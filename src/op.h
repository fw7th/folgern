#include "tensor.h"
#include <vector>

struct Op {
  std::vector<folgern::Tensor *> inputs;
  std::vector<folgern::Tensor *> outputs;
  virtual void forward() = 0;
  virtual ~Op() = default;
};

inline folgern::Tensor *relu(folgern::Tensor *x) {
  auto *op = new ReluOp(x);
  auto *out = new folgern::Tensor();

  op->inputs = {x};
  op->outputs = {out};
  out->producer = op;

  return out;
}

inline folgern::Tensor *matmul(folgern::Tensor *a, folgern::Tensor *b) {
  auto *op = new MatmulOp();
  auto *out = new folgern::Tensor();

  op->inputs = {a, b};
  op->outputs = {out};
  out->producer = op;

  return out;
}
