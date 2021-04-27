import cv2
import torch
import torchvision
import numpy as np

np.random.seed(0)

class ScaleMinSideToSize(object):
    
    def __init__(
        self,
        size: tuple,
    ) -> None:
        
        self.size = np.asarray(size, dtype=np.float)

    def __call__(
        self,
        sample: dict,
    ) -> dict:
        
        h, w, _ = sample['image'].shape
        if h > w:
            f = self.size[0] / w
        else:
            f = self.size[1] / h

        sample['image'] = cv2.resize(sample['image'], None, fx=f, fy=f, interpolation=cv2.INTER_AREA)
        sample['scale_coef'] = f

        if 'landmarks' in sample:
            landmarks = sample['landmarks'].reshape(-1, 2).float()
            landmarks = landmarks * f
            sample['landmarks'] = landmarks.reshape(-1)

        return sample


class CropCenter(object):
    
    def __init__(
        self,
        size: int=128,
    ) -> None:
        
        self.size = size

    def __call__(
        self,
        sample: dict
    ) -> dict:
        
        img = sample['image']
        h, w, _ = img.shape
        margin_h = (h - self.size) // 2
        margin_w = (w - self.size) // 2
        sample['image'] = img[margin_h:margin_h + self.size, margin_w:margin_w + self.size]
        sample['crop_margin_x'] = margin_w
        sample['crop_margin_y'] = margin_h

        if 'landmarks' in sample:
            landmarks = sample['landmarks'].reshape(-1, 2)
            landmarks -= torch.tensor((margin_w, margin_h), dtype=landmarks.dtype)[None, :]
            sample['landmarks'] = landmarks.reshape(-1)

        return sample
    
    
class Cutout(object):

    def __init__(
        self,
        n_holes: int,
        length: int,
    ) -> None:
        
        self.n_holes = n_holes
        self.length = length

    def __call__(
        self,
        sample: dict,
    ) -> dict:
       
        img = sample['image']
        
        _, h, w = img.size()
        
        mask = np.ones((h, w), dtype=np.float32)

        for n in range(self.n_holes):
            y = np.random.randint(h)
            x = np.random.randint(w)

            y1 = np.clip(y - self.length // 2, 0, h)
            y2 = np.clip(y + self.length // 2, 0, h)
            x1 = np.clip(x - self.length // 2, 0, w)
            x2 = np.clip(x + self.length // 2, 0, w)

            mask[y1: y2, x1: x2] = 0

        mask = torch.from_numpy(mask)
        mask = mask.expand_as(img)
        sample['image'] = img * mask

        return sample


class TransformByKeys(object):
    
    def __init__(
        self,
        transform,
        names: list,
    ) -> None:
        
        self.transform = transform
        self.names = set(names)

    def __call__(
        self,
        sample: dict,
    ) -> dict:
        
        for name in self.names:
            if name in sample:
                sample[name] = self.transform(sample[name])

        return sample
    
class RandomLandmarksRotation(object):
    
    def __init__(
        self,
        rotation_limit: float,
    ) -> None:
        
        self.rotation_limit = rotation_limit

    def random_rotation(
        self,
        image,
        landmarks
    ) -> tuple:

        h, w = image.size
        
        angle = np.random.uniform(-self.rotation_limit, self.rotation_limit)
        image = torchvision.transforms.functional.rotate(image, angle)

        landmarks = landmarks.reshape(-1, 2)
        landmarks = torch.cat([landmarks, torch.ones((landmarks.shape[0], 1))], dim=1)
        center = (h / 2, w / 2)
        rad = angle * np.pi / 180.0
        alpha = np.cos(rad)
        beta = np.sin(rad)
        
        M_torch = torch.tensor(
            [[alpha, beta,  center[0]*(1-alpha) - center[1]*beta     ],
             [-beta, alpha, center[0]*beta      + center[1]*(1-alpha)]], 
            dtype=torch.float32)
        
        new_landmark = torch.matmul(landmarks, M_torch.T)

        return image, new_landmark
    
    def __call__(
        self,
        sample
    ) -> dict:
        
        image, landmarks = self.random_rotation(sample['image'], sample['landmarks'])
        sample['image'] = image
        sample['landmarks'] = landmarks.flatten()
        
        return sample
    
    
class UnNormalize(object):
    
    def __init__(
        self,
        mean: list,
        std: list,
    ) -> None:
        
        self.mean = mean
        self.std = std

    def __call__(
        self,
        tensor
    ) -> torch.tensor:

        for t, m, s in zip(tensor, self.mean, self.std):
            t.mul_(s).add_(m)
            # The normalize code -> t.sub_(m).div_(s)
            
        return tensor