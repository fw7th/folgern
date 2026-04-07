#include "tensor.h"

namespace folgern {

void Tensor::spawn(int _w, DType _dtype, Allocator *_allocator) {
  if (dims == 1 && w == _w && dtype == _dtype && allocator == _allocator)
    return;

  release();

  allocator = _allocator;
  dtype = _dtype;

  dataptr = allocator->allocate(calcBytes(_w, _dtype));
}

}; // namespace folgern
