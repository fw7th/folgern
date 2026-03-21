#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <cstdlib>

namespace folgern {

class Allocator {
public:
  Allocator() {}
  void *allocate(size_t bytes) { return std::malloc(bytes); }
  void deallocate(void *ptr) {
    std::free(ptr);
    ptr = nullptr;
  }
};

static int incrementRef(int *addr, int delta) {
  int tmp = *addr;
  *addr += delta;
  return tmp;
}
} // namespace folgern

#endif
