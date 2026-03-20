#include <cstddef>
#include <cstdlib>
#include <memory>

namespace folgern {

class Allocator {
public:
  Allocator() {}
  void *allocate(size_t bytes) { return std::make_shared<void>(bytes); }
  void deallocate(void *ptr) { free(ptr); }
};
} // namespace folgern
