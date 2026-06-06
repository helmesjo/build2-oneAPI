# liboneapi-openmp

## Versions

  Platform  Component ID                       Version
  --------  ------------                       -------
  linux     intel.oneapi.lin.openmp            2026.0.0+947
  windows   intel.oneapi.win.openmp            2026.0.0+944

Content manifest basename:
  linux:   intel.oneapi.lin.compiler.content
  windows: intel.oneapi.win.compiler.content

The openmp component ships as a single payload (no separate devel/runtime).
The build2 package uses one extract group: extract{openmp-runtime}.

## Tarball layout

Tarballs extract under _installdir/compiler/<ver>/ which maps to
openmp-runtime/ after the version-segment strip in redist.build.

  openmp-runtime/lib/libiomp5.so          - OpenMP runtime  (linux)
  openmp-runtime/lib/libiomp5_db.so       - OMPD debugger extension
  openmp-runtime/lib/libiompstubs5.so     - stubs
  openmp-runtime/lib/libarcher.so         - ThreadSanitizer plugin (not linked)
  openmp-runtime/lib/libomptarget.so      - offload target dispatch
  openmp-runtime/lib/libomptarget.sycl.wrap.so

  openmp-runtime/bin/libiomp5md.dll       - OpenMP runtime  (windows, 'md' = MSVC DLL CRT)
  openmp-runtime/bin/libiomp5md_db.dll
  openmp-runtime/bin/libiompstubs5md.dll
  openmp-runtime/bin/omptarget.dll
  openmp-runtime/bin/omptarget.sycl.wrap.dll

Note: libiomp5.so carries no SONAME version suffix on Linux.
Note: omptarget.rtl.level0/opencl/unified_runtime DLLs were present in earlier
releases but are absent in 2026.0.0 on both platforms.

## build2 targets

  Target              Linux libs                           Windows libs / libi
  ------              ----------                           -------------------
  openmp-rt           libiomp5.so                          libiomp5md.dll
                      libiomp5_db.so                       libiomp5md_db.dll
                      libiompstubs5.so                     libiompstubs5md.dll
                      -                                    libi: libiomp5md.lib
                      -                                    libi: libiompstubs5md.lib

  openmp-omptarget    libomptarget.so                      omptarget.dll
                      libomptarget.sycl.wrap.so            omptarget.sycl.wrap.dll
                      depends: openmp-rt                   libi: omptarget.lib
                                                           depends: openmp-rt

## Platform notes

- Linux test for openmp-omptarget is disabled: libomptarget.so depends on
  intel.oneapi.lin.compilers-common.runtime (libimf, libsvml, libirng,
  libintlc) and intel.oneapi.lin.dpcpp-cpp-common.runtime (libsycl,
  libur_loader) - neither packaged yet.
- Windows omptarget shipped .rtl.* DLLs in earlier releases. They are absent
  in 2026.0.0 on both platforms.
