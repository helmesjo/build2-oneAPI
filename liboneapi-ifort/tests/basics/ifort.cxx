// ifort smoke test: verifies linking to libifcoremd and the ISO Fortran C
// binding interface by establishing a rank-1 descriptor and querying it.
#undef NDEBUG
#include <cassert>

#include <ISO_Fortran_binding.h>

int main ()
{
  int            x[]  = {42};
  CFI_index_t    ext  = 1;
  CFI_CDESC_T(1) buf  = {};
  CFI_cdesc_t*   dv   = reinterpret_cast<CFI_cdesc_t*> (&buf);

  assert (CFI_establish (dv, x, CFI_attribute_other,
                         CFI_type_int, sizeof (int), 1, &ext) == CFI_SUCCESS);
  assert (CFI_is_contiguous (dv) != 0);
}
