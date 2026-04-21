#include "tensor.h"

void Tensor::create(int _size, Allocator *_allocator) {
  if (w == _size && allocator == _allocator)
    return;

  // release();

  allocator = _allocator;
  w = _size;

  dataptr = allocator->allocate(_size);
}
