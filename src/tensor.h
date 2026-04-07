#ifndef TENSOR_H
#define TENSOR_H

#include "allocator.h"
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <iostream>

// dtypes and sizes in bytes
enum class DType { FLOAT32, INT32, UINT32, FLOAT64 };

inline size_t dtypeSize(DType dt) {
  switch (dt) {
  case DType::FLOAT32:
    return sizeof(float);
  case DType::INT32:
    return sizeof(int32_t);
  case DType::UINT32:
    return sizeof(uint32_t);
  case DType::FLOAT64:
    return sizeof(double);
  }
  return 0;
}

namespace folgern {

class Tensor {
public:
  // empty tensor
  Tensor();
  // 1d tensor
  Tensor(int w, Allocator *allocator = 0, DType dtype = DType::FLOAT32);
  // 2d tensor
  Tensor(int w, int h, Allocator *allocator = 0, DType dtype = DType::FLOAT32);
  // copy
  // Tensor(const Tensor &t);
  // delete
  ~Tensor();
  // allocate tensor space
  void spawn(int w, DType dtype, Allocator *allocator = 0);
  void spawn(int w, int h, DType dtype, Allocator *allocator = 0);
  // calc no. of bytes
  size_t calcBytes(int w, DType dtype);
  size_t calcBytes(int w, int h, DType dtype = DType::FLOAT32);
  // fill tensor w/ numbs of dtype
  template <typename T> void fill(T f);
  // decrement refcount
  void release();
  // increment refcount
  void addRef();

  size_t total() const;

  // refcount for Tensor
  int *refcount;

  // pointer to stored data
  void *dataptr;

  // leaf node or not
  // Op *producer = nullptr; // nullptr == leaf node

  // memory allocator
  Allocator *allocator;

  // the dimension rank
  int dims;

  int w;
  int h;
  int c;

  DType dtype;
};

inline Tensor::~Tensor() { release(); }
inline Tensor::Tensor(int _w, Allocator *_allocator, DType _dtype)
    : dataptr(0), refcount(0), allocator(0), dims(0), w(0), h(0), c(0) {
  spawn(_w, _dtype, _allocator);
}

inline Tensor::Tensor(int _w, int _h, Allocator *_allocator, DType _dtype)
    : dataptr(0), refcount(0), allocator(0), dims(0), w(0), h(0), c(0) {
  spawn(_w, _h, _dtype, _allocator);
}
inline size_t Tensor::calcBytes(int _w, DType _dtype) {
  return (_w)*dtypeSize(_dtype);
}

inline size_t Tensor::calcBytes(int _w, int _h, DType _dtype) {
  return (_w * _h) * dtypeSize(_dtype);
}

// TODO: Rewrite fill() to make it generalizable, need memory alignment to do
// it, this only works for 1d rn
template <typename T> inline void Tensor::fill(T _f) {
  int size = (int)w;
  T *ptr = (T *)dataptr;

  for (int i = 0; i < size; i++) {

    std::cout << "cows";
    ptr[i] = _f;
    printf("Tensor filled with address %p, and value %f\n", &ptr[i], ptr[i]);
  }
}

inline void Tensor::release() {
  if (refcount && incrementRef(refcount, -1) == 1) {
    allocator->deallocate(dataptr);
  }

  dataptr = 0;

  // w = 0;
  h = 0;
  c = 0;

  refcount = 0;
}

} // namespace folgern

#endif
