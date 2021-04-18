import numpy as np

from scipy import sparse


def add_dim(data):
        
    return sparse.hstack(
        blocks=[np.ones((data.shape[0], 1), int), data],
        dtype=int,
        format='lil',
    )