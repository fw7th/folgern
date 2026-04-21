#include "tensor.h"
#include <vector>

class Op {
  Tensor *output;

  Op(Tensor input);
};

inline Op::Op(Tensor input) {
  Tensor output(input.w);
  for (int i = 0; i < input.w; i++) {
    float x = *(input.dataptr + i);
    float result = (x > 0.0f) ? x : 0.0f;
    *(output.dataptr + i) = result;

    printf("Ptr Address: %p, Ptr Value: %f\n", (output.dataptr + i),
           *(output.dataptr + i));
  }
}
