import os
import torch
import numpy  as np
import pandas as pd
from tqdm.notebook import tqdm

from utils.dataset import ThousandLandmarksDataset


def restore_landmarks_batch(landmarks, fs, margins_x, margins_y):
    landmarks[:, :, 0] += margins_x[:, None]
    landmarks[:, :, 1] += margins_y[:, None]
    landmarks /= fs[:, None, None]
    return landmarks


def predict(model, loader, device, num_points):
    
    model.eval()
    predictions = np.zeros((len(loader.dataset), num_points, 2))
    for i, batch in enumerate(tqdm(loader, total=len(loader), desc='evaluation')):
        images = batch['image'].to(device)

        with torch.no_grad():
            pred_landmarks = model(images).cpu()
        pred_landmarks = pred_landmarks.numpy().reshape((len(pred_landmarks), num_points, 2))  # B x NUM_PTS x 2

        fs = batch['scale_coef'].numpy()  # B
        margins_x = batch['crop_margin_x'].numpy()  # B
        margins_y = batch['crop_margin_y'].numpy()  # B
        prediction = restore_landmarks_batch(pred_landmarks, fs, margins_x, margins_y)  # B x NUM_PTS x 2
        predictions[i * loader.batch_size: (i + 1) * loader.batch_size] = prediction

    return predictions
    

def submit(model, transforms, test_path, path2save, device, num_points):
    
    test_dataset = ThousandLandmarksDataset(
        test_path,
        transforms,
        split='test',
    )
    test_dataloader = torch.utils.data.DataLoader(
        test_dataset,
        batch_size=4,
        num_workers=4,
        pin_memory=True,
        shuffle=False,
        drop_last=False,
    )
    
    test_predictions = predict(model, test_dataloader, device, num_points)
    
    wf = open(path2save, 'w')
    wf.write('file_name,' + ','.join('Point_M%d_X,Point_M%d_Y' % (i, i) for i in range(30)) + '\n')
    
    mapping = pd.read_csv(os.path.join(test_path, 'test_points.csv'), delimiter='\t')
    
    for i, row in mapping.iterrows():
        file_name = row[0]
        point_index_list = np.array(eval(row[1]))
        points_for_image = test_predictions[i]
        needed_points = points_for_image[point_index_list].astype(np.int)
        wf.write(file_name + ',' + ','.join(map(str, needed_points.reshape(2 * len(point_index_list)))) + '\n')
        
    wf.close()
    