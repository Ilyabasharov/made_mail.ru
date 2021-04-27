import torch
import timm
import torchvision


def getModelTorchvision(
    backbone_type: str,
    n_output: int,
    device: torch.device,
):
    
    net = getattr(torchvision.models, backbone_type)(pretrained = True)
    net.fc = torch.nn.Linear(net.fc.in_features, n_output)
    net.fc.requires_grad_(True)
    
    return net.to(device)

def getModelTIMM(
    backbone_type: str,
    n_output: int,
    device: torch.device,
):
    
    net = timm.create_model(backbone_type, pretrained=False)
    net.requires_grad_(True)
    
    net.fc = torch.nn.Sequential(
        torch.nn.Linear(net.fc.in_features, net.fc.in_features),
        torch.nn.ReLU(inplace=True),
        torch.nn.Linear(net.fc.in_features, n_output),
    )
    net.fc.requires_grad_(True)
    
    return net.to(device)