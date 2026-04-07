#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <cstdlib>

namespace folgern {

static inline size_t alignSize(size_t sz, int n) { return (sz + n - 1) & -n; }

class Allocator {
public:
  Allocator() {}
  void *allocate(size_t bytes);
  void deallocate(void *ptr);
};

inline void *Allocator::allocate(size_t bytes) { return std::malloc(bytes); }
inline void Allocator::deallocate(void *ptr) {
  std::free(ptr);
  ptr = nullptr;
}
static inline int incrementRef(int *addr, int delta) {
  int tmp = *addr;
  *addr += delta;
  return tmp;
}
} // namespace folgern

#endif
