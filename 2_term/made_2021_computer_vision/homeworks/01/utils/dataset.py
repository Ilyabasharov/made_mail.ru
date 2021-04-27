import os
import cv2
import torch
import numpy as np

class ThousandLandmarksDataset(torch.utils.data.Dataset):
    def __init__(
        self,
        root: str,
        transforms,
        split: str='train',
        train_size: float=0.8,
    ) -> None:
        
        super().__init__()
        
        self.root = root
        if split in ('train', 'val'):
            landmark_file_name = os.path.join(root, 'landmarks.csv')
        else:
            landmark_file_name = os.path.join(root, 'test_points.csv')
            
        images_root = os.path.join(root, 'images')
        
        if os.path.exists('ignore_files.txt'):
            ignore_files = set(np.loadtxt('ignore_files.txt', dtype=str))
        else:
            ignore_files = set(['0'])

        self.image_names, self.landmarks = [], []

        with open(landmark_file_name, 'rt') as fp:
            num_lines = sum(1 for line in fp) - 1

        with open(landmark_file_name, 'rt') as fp:
            for i, line in enumerate(fp):
                if i == 0:
                    continue  # skip header
                if split == 'train' and i == int(train_size * num_lines):
                    break  # reached end of train part of data
                elif split == 'val' and i < int(train_size * num_lines):
                    continue  # has not reached start of val part of data
                    
                elements = line.strip().split('\t')
                image_name = os.path.join(images_root, elements[0])
                
                if not os.path.exists(image_name):
                    continue
                    
                if image_name in ignore_files:
                    continue
                    
                self.image_names.append(image_name)

                if split in ('train', 'val'):
                    landmarks = list(map(int, elements[1:]))
                    landmarks = np.array(landmarks, dtype=np.int).reshape((len(landmarks) // 2, -1))
                    self.landmarks.append(landmarks)

        if split in ('train', 'val'):
            self.landmarks = self.landmarks
        else:
            self.landmarks = None

        self.transforms = transforms

    def __getitem__(
        self,
        idx: int,
    ) -> dict:
        
        sample = {}
        if self.landmarks is not None:
            landmarks = self.landmarks[idx]
            sample['landmarks'] = torch.from_numpy(landmarks)
            
        assert os.path.exists(self.image_names[idx]), self.image_names[idx]
            
        image = cv2.imread(self.image_names[idx])
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        sample['image'] = image
        sample['idx'] = torch.tensor(idx)
        
        if self.transforms is not None:
            sample = self.transforms(sample)

        return sample

    def __len__(
        self,
    ) -> int:
        
        return len(self.image_names)