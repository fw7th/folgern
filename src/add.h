#include "tensor.h"
#include <cstdio>
#include <initializer_list>

struct Add {
  void operator()(std::initializer_list<const Tensor *> parents,
                  Tensor &child) {
    if (parents.size() == 0)
      return;

    for (const auto *parent : parents) {
      if (parent->w != child.w) {
        printf("Tensor sizes do not match\n");
        return;
      }
    }

    for (int i = 0; i < child.w; i++) {
      float sum = 0.0f;
      for (const auto *parent : parents) {
        sum += parent->dataptr[i];
      }
      child.dataptr[i] = sum;
    }
  }
};
