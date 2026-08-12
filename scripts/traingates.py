import torch
import torch.nn as nn
import torch.optim as optim


# --- Simple model: 2 inputs -> 1 output with sigmoid ---
class GateModel(nn.Module):
    def __init__(self):
        super().__init__()
        self.linear = nn.Linear(2, 1)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        return self.sigmoid(self.linear(x))


# --- Training setup ---
def train_gate(name, X, y, epochs=5000, lr=0.1):
    model = GateModel()
    criterion = nn.BCELoss()
    optimizer = optim.SGD(model.parameters(), lr=lr)

    for epoch in range(epochs):
        optimizer.zero_grad()
        outputs = model(X)
        loss = criterion(outputs, y)
        loss.backward()
        optimizer.step()

        if (epoch + 1) % 1000 == 0:
            print(f"[{name}] Epoch {epoch + 1}/{epochs}, Loss: {loss.item():.6f}")

    return model


# --- Data: AND and OR truth tables ---
# Inputs
X = torch.tensor([[0.0, 0.0], [0.0, 1.0], [1.0, 0.0], [1.0, 1.0]])

# Labels
y_and = torch.tensor([[0.0], [0.0], [0.0], [1.0]])
y_or = torch.tensor([[0.0], [1.0], [1.0], [1.0]])

# --- Train ---
print("Training AND gate...")
model_and = train_gate("AND", X, y_and)

print("\nTraining OR gate...")
model_or = train_gate("OR", X, y_or)


# --- Evaluate ---
def evaluate(name, model, X, y):
    with torch.no_grad():
        preds = model(X).round()
        print(f"\n{name} Gate Predictions:")
        for i in range(len(X)):
            print(
                f"  {X[i].int().tolist()} -> {preds[i].item():.0f} (true: {y[i].item():.0f})"
            )


evaluate("AND", model_and, X, y_and)
evaluate("OR", model_or, X, y_or)

# --- Save state dicts ---
torch.save(model_and.state_dict(), "and_gate.pt")
torch.save(model_or.state_dict(), "or_gate.pt")
print("\nSaved: and_gate.pt, or_gate.pt")
