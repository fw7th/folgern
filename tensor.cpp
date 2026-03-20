#include "tensor.h"
#include "allocator.h"
#include <cstdio>
#include <cstdlib>

namespace folgern {
void Tensor::spawn(int _w, DType dtype, Allocator *_allocator) {
  allocator = _allocator;
  allocator->allocate(calcBytes(_w, dtype));
}

void Tensor::spawn(int _w, int _h, DType dtype, Allocator *_allocator) {
  allocator = _allocator;
  allocator->allocate(calcBytes(_w, _h, dtype));
}
}; // namespace folgern
