struct Allocator {
  float *allocate(int size) {
    float *ptr = new float[size];
    return ptr;
  }
  void deallocate(void *ptr) {
    delete[] static_cast<float *>(ptr);
    ptr = nullptr;
  }
};
