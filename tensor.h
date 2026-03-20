#include "allocator.h"
#include <cstddef>
#include <cstdint>

// dtypes and sizes in bytes
enum class DType { FLOAT32, INT32, UINT32, FLOAT64 };
size_t dtypeSize(DType dt) {
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
  Tensor(int w, DType dtype = DType::FLOAT32, Allocator *allocator);
  // 2d tensor
  Tensor(int w, int h, DType dtype = DType::FLOAT32, Allocator *allocator);
  // allocate tensor space
  void spawn(int w, DType dtype, Allocator *allocator);
  void spawn(int w, int h, DType dtype = DType::FLOAT32, Allocator *allocator);
  // calc no. of bytes
  size_t calcBytes(int w, DType dtype);
  size_t calcBytes(int w, int h, DType dtype = DType::FLOAT32);
  // fill tensor w/ numbs of dtype
  template <typename T> void fill(T f);
};

size_t Tensor::calcBytes(int _w, DType dtype) { return (_w)*dtypeSize(dtype); }

size_t Tensor::calcBytes(int _w, int _h, DType dtype) {
  return (_w * _h) * dtypeSize(dtype);

  // TODO: Rewrite fill() to make it generalizable
}

} // namespace folgern
