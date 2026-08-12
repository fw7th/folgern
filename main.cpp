#include "add.h"
#include "tensor.h"

int main() {
  Tensor a(5);
  a.fill(2.5f);

  Tensor b(5);
  b.fill(3.0f);

  Tensor c(5);

  Add add_op;
  add_op({&a, &b}, c); // if you use the variadic Add

  return 0;
}
