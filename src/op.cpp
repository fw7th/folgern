#include "op.h"
#include <iostream>

struct ReluOp : Op {
  ReluOp() {
    if (inputs.size() > 1) {
      std::cout << "RELU OP takes one tensor only.";
      return;
    }
    for (int tensor : inputs) {
      std::cout << tensor->dataptr;
    }
  }
};
