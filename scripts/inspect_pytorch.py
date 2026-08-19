import torch

# Load your full TorchScript model
model = torch.jit.load("./pt_models/and_gate_full.pt")

# 1. View the Python-like forward pass (easiest to read)
print("--- PYTHON CODE ---")
print(model.code)

# 2. View the raw intermediate representation (IR) graph
print("--- RAW GRAPH IR ---")
print(model.graph)

# 3. View the graph with inlined submodules (flattens everything)
print("--- INLINED GRAPH ---")
print(model.inlined_graph)
