# folgern

**A bare‑bones CPU inference engine for computer vision.**

This is not a production framework. It's a hands‑on project to understand the low‑level mechanics of CPU inference: tensor layouts, memory allocation, operator execution, and graph conversion. No GPU, no CUDA,  just Intel x86 for now, with an eye on ARM later.

## Current state

- **Tensor**: 1D `float` storage with optional `Allocator` for custom memory management [5†L2-L27]
- **Operator**: `Add` – variadic element‑wise addition [6†L2-L9]
- **Allocator**: simple `new[]`/`delete[]` wrapper [7†L2-L4]
- **Build**: CMake, C++17, `-O3 -mtune=native` for Release [4†L2-L10]
- **Example**: `main.cpp` allocates two tensors, adds them, prints results [3†L2-L4]

## What's next (the converter)

The immediate goal is a **PyTorch → folgern converter**. We'll load TorchScript models (`torch.jit.save`), traverse the graph, extract weights, and emit `.folgern` model files that the runtime can execute.

The work is split into incremental issues:

| Issue | What it delivers |
|-------|-------------------|
| 1 | `.folgern` binary serialization format |
| 2 | TorchScript graph traversal (see the ops) |
| 3 | Weight extraction → folgern tensors |
| 4 | Operator registry (`aten::*` → folgern ops) |
| 5 | End‑to‑end conversion (weights + ops → `.folgern`) |
| 6 | (Future) Control flow: `prim::If`, `prim::Loop` |

Once the converter works for gate‑level models (AND, OR), we'll scale up to real CV workloads.

## Building

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make
./main

## Philosophy
- Small scope: one operator, one layer at a time.
- Learn by doing -> every component is written from scratch to expose the trade‑offs.
- CPU‑first -> Intel for now, ARM when the fundamentals are solid.
- No GPU, no third‑party inference engines, just C++, memory, and loops.
