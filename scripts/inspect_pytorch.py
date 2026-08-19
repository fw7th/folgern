import torch

# Load your full TorchScript model
model = torch.jit.load("pt_models/and_gate_full.pt")

# 1. View the Python-like forward pass (easiest to read)
print("--- PYTHON CODE ---")
print(model.code)

# 2. View the raw intermediate representation (IR) graph
print("--- RAW GRAPH IR ---")
print(model.graph)

# 3. View the graph with inlined submodules (flattens everything)
print("--- INLINED GRAPH ---")
print(model.inlined_graph)


def extract_graph(model):
    # Get the weights separately (or fetch them via node inputs)
    state_dict = model.state_dict()

    # Iterate through all nodes in the forward graph
    for node in model.graph.nodes():
        # `kind()` gives the operation name (e.g., 'aten::linear', 'aten::sigmoid')
        op_name = node.kind()
        print(f"Found operation: {op_name}")

        # Get input names for this node
        inputs = [inp.unique() for inp in node.inputs()]
        # Get output names for this node
        outputs = [out.unique() for out in node.outputs()]

    print("INPUTS: ", inputs)


extract_graph(model)
