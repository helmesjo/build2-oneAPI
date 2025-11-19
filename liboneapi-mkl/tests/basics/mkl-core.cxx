// mkl-core smoke test
#include <mkl.h>
#undef NDEBUG
#include <cassert>

int main() {
  MKLVersion v{};
  MKL_Get_Version(&v);
  assert(v.MajorVersion >= 1);
}
