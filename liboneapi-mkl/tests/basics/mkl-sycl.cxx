// mkl-sycl smoke test
#include <oneapi/mkl.hpp>
#undef NDEBUG
#include <cassert>

int main() {
  sycl::queue q;
  assert(q.is_host() || q.get_device().is_gpu());
}
