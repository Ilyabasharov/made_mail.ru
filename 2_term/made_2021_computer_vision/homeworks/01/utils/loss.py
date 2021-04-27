import math
import torch

def identity(x):
    return x


class WingLoss(torch.nn.Module):
    
    def __init__(
        self,
        w: float=10,
        eps: float=2,
        reduction: str='mean',
    ) -> None:

        assert reduction is None or reduction in ('mean', 'sum')
        
        super().__init__()
        self._w = w
        self._eps = eps
        self._constant = self._w * (1 - math.log(1 + self._w / self._eps))
        if reduction is None:
            self._reduction_fn = identity
        elif reduction == 'mean':
            self._reduction_fn = torch.mean
        elif reduction == 'sum':
            self._reduction_fn = torch.sum

    def forward(
        self,
        predicted: torch.tensor,
        target: torch.tensor,
    ):
        
        """Compute wing loss
        Predicted and target have size batch_size x 2 * num_landmarks
        """

        diff = torch.abs(predicted - target)

        log_mask = diff < self._w
        like_l1_mask = ~log_mask

        diff[log_mask] = self._w * torch.log(1 + diff[log_mask] / self._eps)
        diff[like_l1_mask] -= self._constant

        loss_by_sample = diff.sum(dim=1)

        return self._reduction_fn(loss_by_sample)
    