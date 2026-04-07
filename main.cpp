#include "memory"
#include "tensor.h"
#include <cstdio>

int main() {
  folgern::Tensor a(5);
  folgern::Tensor b(5);

  a.fill(2.5);
  b.fill(2.5);

  return 0;
}

// CREATE OPERATION TO ADD TWO TENSORS, CREATE RELU OPERATION
// WE WERE ABOUT TO COMPILE RELU OP, THEN FOUND OUT FILL ISN'T WORKING ANYMORE,
// DEBUG THIS!
