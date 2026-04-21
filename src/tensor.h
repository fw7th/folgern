#ifndef TENSOR_H
#define TENSOR_H

#include "allocator.h"
#include <cstdio>

/* Let's create a 1D tensor for now.*/
struct Tensor {
  // empty tensor
  Tensor();
  // 1d tensor
  Tensor(int w, Allocator *allocator = 0);
  // copy
  Tensor(const Tensor &t);
  // delete
  ~Tensor();
  // allocate tensor space
  void create(int size, Allocator *allocator);
  // refcount++
  void addref();
  // fill tensor w/ numbs of dtype
  void fill(float f);
  // free tensor memory
  void release();

  int w;

  // pointer to stored data
  float *dataptr;

  // reference counter
  int *refcount;

  // memory allocator
  Allocator *allocator;

  // Op *op_ptr = nullptr;
};

inline Tensor::Tensor(int _w, Allocator *_allocator)
    : w(0), allocator(nullptr) {
  create(_w, _allocator);
}

inline Tensor::~Tensor() { release(); }

inline void Tensor::fill(float f) {
  printf("In fill method\n");
  printf("W = %d\n", w);
  for (int i = 0; i < w; i++) {
    *(dataptr + i) = f;
    printf("Ptr Address: %p, Ptr Value: %f\n", (dataptr + i), *(dataptr + i));
  }
}

inline void Tensor::addref() { *refcount + 1; }

inline void Tensor::release() {
  /*
if (*refcount == 1) {
  allocator->deallocate(dataptr);
}
  */
  allocator->deallocate(dataptr);
}

#endif
