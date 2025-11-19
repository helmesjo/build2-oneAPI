// mkl-rt smoke test
#include <cstring>
#include <mkl.h>
#undef NDEBUG
#include <cassert>

int main() {
  char buf[2048]{};
  MKL_Get_Version_String(buf, sizeof(buf));
  assert(std::strstr(buf, "Intel") != nullptr);
}
