#ifndef TENSOR_H
#define TENSOR_H

#include "allocator.h"
#include <cstdio>

struct Tensor {
  Tensor();
  explicit Tensor(int w, Allocator *allocator = nullptr);
  ~Tensor();

  Tensor(const Tensor &) = delete;
  Tensor &operator=(const Tensor &) = delete;

  Tensor(Tensor &&other) noexcept;
  Tensor &operator=(Tensor &&other) noexcept;

  void create(int size, Allocator *allocator);
  void fill(float f);
  void release();

  int w = 0;
  float *dataptr = nullptr;
  Allocator *allocator = nullptr;
};

inline Tensor::Tensor() = default;

inline Tensor::Tensor(int _w, Allocator *_allocator) { create(_w, _allocator); }

inline Tensor::~Tensor() { release(); }

inline Tensor::Tensor(Tensor &&other) noexcept
    : w(other.w), dataptr(other.dataptr), allocator(other.allocator) {
  other.w = 0;
  other.dataptr = nullptr;
  other.allocator = nullptr;
}

inline Tensor &Tensor::operator=(Tensor &&other) noexcept {
  if (this != &other) {
    release();
    w = other.w;
    dataptr = other.dataptr;
    allocator = other.allocator;
    other.w = 0;
    other.dataptr = nullptr;
    other.allocator = nullptr;
  }
  return *this;
}

inline void Tensor::create(int _size, Allocator *_allocator) {
  if (w == _size && allocator == _allocator && dataptr != nullptr)
    return;

  release();

  allocator = _allocator;
  w = _size;

  if (allocator) {
    dataptr = allocator->allocate(_size);
  } else {
    dataptr = new float[_size]; // direct dynamic allocation
  }
}

inline void Tensor::fill(float f) {
  if (dataptr == nullptr) {
    printf("ERROR: fill() called on tensor with null dataptr\n");
    return;
  }
  printf("In fill method\n");
  printf("W = %d\n", w);
  for (int i = 0; i < w; i++) {
    dataptr[i] = f;
    printf("Ptr Address: %p, Ptr Value: %f\n", (void *)(dataptr + i),
           dataptr[i]);
  }
}

inline void Tensor::release() {
  if (dataptr == nullptr)
    return;

  if (allocator) {
    allocator->deallocate(dataptr);
  } else {
    delete[] dataptr; // we allocated it directly, so we free it directly
  }

  dataptr = nullptr;
  w = 0;
  allocator = nullptr;
}

#endif
