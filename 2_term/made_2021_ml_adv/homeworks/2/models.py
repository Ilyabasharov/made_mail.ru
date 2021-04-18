import scipy as sp
import numpy as np

from scipy import sparse
import matplotlib.pyplot as plt

from features import (
    team_answer_estimation,
    create_test_prediction,
)

from utils import (
    add_dim,
)

class ProbaRegression:
    
    def __init__(
        self,
        init_weights=None,
        epochs=1e4,
        lr=1e1,
        bs=1e4,
        tol=1e-4,
        viz=True,
        axis=None,
        fig=None
    ) -> None:
        
        self.w = init_weights
        self.epochs = int(epochs)
        self.lr = lr
        self.bs = int(bs)
        self.tol = tol
        self.viz = viz
        
        if self.viz:
            self.axis = axis
            self.fig = fig
            self.axis.set_xlabel('epoch')
            self.axis.set_ylabel('metric')
    
    def fit(self, X, y):
        
        if self.w is None:
            self.w = np.random.normal(size=X.shape[1])
        
        if self.viz:
            losses = []
        
        for i in range(self.epochs):
            
            idx = np.random.choice(X.shape[0], self.bs)
            
            x_batch, y_batch_gt = X[idx], y[idx]
            y_batch_pred = self.sigmoid(x_batch @ self.w)
            
            grad = x_batch.T @ (y_batch_pred - y_batch_gt) / self.bs
            self.w -= self.lr * grad
            
            if self.viz:
                self.axis.clear()
                losses.append(self.log_loss(y_batch_gt, y_batch_pred))
                self.axis.plot(losses, label='log_loss')
                self.fig.canvas.draw()
                plt.grid(True)
            
    def predict_proba(self, X):
        
        positive_preds = self.sigmoid(X @ self.w).T
        
        return np.column_stack([(1. - positive_preds), positive_preds])
    
    @staticmethod
    def mae(y, p):
        
        return np.abs(y - p).mean()
    
    @staticmethod
    def log_loss(y, p):
        
        return -np.mean(y * np.log(p) + (1. - y) * np.log(1. - p))
    
    @staticmethod
    def sigmoid(x):
        
        return np.exp(-np.logaddexp(0, -x))
     

class EM:
    
    def __init__(
        self,
        dataset,
        X, y, player_to_idx,
        epochs_em,
        epochs_pr,
        viz=True,
    ) -> None:
        
        axes1d = [None, None]
        
        self.viz = viz
        if self.viz:
            self.fig, axes1d = plt.subplots(2, 1, figsize=(8, 4))
            self.axis = axes1d[1]
            self.axis.set_xlabel('epoch')
            self.axis.set_ylabel('correlation')
        
        self.pr = ProbaRegression(
            init_weights=None,
            epochs=epochs_pr,
            viz=viz,
            axis=axes1d[0],
            fig=self.fig,
        )
        
        self.X = add_dim(X)
        self.y = y
        self.dataset = dataset
        self.player_to_idx = player_to_idx
        
        self.epochs = int(epochs_em)
         
    def fit(self, test_on=None):
        
        self.spearman, self.kendall = [], []
        
        # initial M step
        self.pr.fit(self.X, self.y)
        
        for i in range(self.epochs):
            
            #decrease lr 
            self.pr.lr /= 1.2
            
            #proba if each player answered on each question
            M_step_pred = self.pr.predict_proba(self.X)
            
            # E step;
            #team will answer on question estimation based on prev prediction
            team_success = team_answer_estimation(self.dataset, self.player_to_idx, M_step_pred)
            z = (M_step_pred[..., 1] / team_success).clip(0, 1)
            
            z[self.y == 0] = 0.
            
            # M step;
            self.pr.fit(self.X, z)
            
            if test_on is not None:
                rating_pred, rating_gt = create_test_prediction(
                    dataset=test_on,
                    player_to_idx=self.player_to_idx,
                    model=self.pr,
                    n_features=self.X.shape[1],
                )
                
                spearman = [
                    sp.stats.spearmanr(rating_gt[i], rating_pred[i]).correlation
                    for i in range(len(rating_pred))
                ]

                kendall = [
                    sp.stats.kendalltau(rating_gt[i], rating_pred[i]).correlation
                    for i in range(len(rating_pred))
                ]
                
                self.spearman.append(np.nanmean(spearman))
                self.kendall.append(np.nanmean(kendall))
                
                if self.viz:
                    self.axis.clear()
                    self.axis.plot(self.spearman, label='spearman')
                    self.axis.plot(self.kendall, label='kendall')
                    self.fig.canvas.draw()
                    plt.grid(True)
                    plt.legend();