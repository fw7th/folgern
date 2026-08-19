import torch

data = torch.load("./pt_models/or_gate_full.pt", map_location="cpu")
if isinstance(data, dict):
    for name, tensor in data.items():
        print(f"Parameter: {name}, shape: {tensor.shape}, dtype: {tensor.dtype}")
        # Optionally print a few values:
        # print(tensor.flatten()[:5])
print(type(data))  # Usually dict, OrderedDict, or a module object
