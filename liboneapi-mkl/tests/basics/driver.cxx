#include <cstdio>
#include <cstring>
#include <mkl.h>

#undef NDEBUG
#include <cassert>

int main() {
  char buffer[2048]{};
  mkl_get_version_string(buffer, sizeof(buffer));
  printf("%s\n", buffer);
  assert(strstr(buffer, "oneAPI") != nullptr);
}
