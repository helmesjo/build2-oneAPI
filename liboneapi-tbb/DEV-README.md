# liboneapi-tbb

## Versions

  Platform  Component ID                       Version
  --------  ------------                       -------
  linux     intel.oneapi.lin.tbb.runtime       2023.0.0+724
  linux     intel.oneapi.lin.tbb.devel         2023.0.0+724
  windows   intel.oneapi.win.tbb.devel         2023.0.0+716

Content manifest basename:
  linux:   intel.oneapi.lin.tbb_oneapi.content
  windows: intel.oneapi.win.tbb_oneapi.content

## Tarball layout

### tbb.runtime  ->  extract{tbb-runtime}

_installdir/tbb/<ver>/ maps to tbb-runtime/ after the version-segment strip.

  tbb-runtime/lib/libtbb.so{,.12,.12.18}
  tbb-runtime/lib/libtbbmalloc.so{,.2,.2.18}
  tbb-runtime/lib/libtbbmalloc_proxy.so{,.2,.2.18}
  tbb-runtime/lib/libtbbbind.so{,.3,.3.18}
  tbb-runtime/lib/libtbbbind_2_0.so{,.3,.3.18}
  tbb-runtime/lib/libtbbbind_2_5.so{,.3,.3.18}

  tbb-runtime/bin/tbb12.dll            (windows)
  tbb-runtime/bin/tbbmalloc.dll
  tbb-runtime/bin/tbbmalloc_proxy.dll
  tbb-runtime/bin/tbbbind.dll
  tbb-runtime/bin/tbbbind_2_0.dll
  tbb-runtime/bin/tbbbind_2_5.dll

Note: the unversioned .so symlinks (libtbb.so etc.) live in the runtime
tarball, not devel. The tbb-devel build2 target therefore references paths
under tbb-runtime/ for its libs.

### tbb.devel  ->  extract{tbb-devel}

  tbb-devel/include/oneapi/tbb/*.h     - public headers  (linux)
  tbb-devel/lib/*_debug.so{,.N,.N.M}  - debug variants  (linux)
  tbb-devel/lib/cmake/tbb/            - CMake integration
  tbb-devel/lib/pkgconfig/tbb.pc

Windows has no separate devel extract; headers and import libs ship
together in the runtime tarball (not yet verified).

## build2 targets

  Target              Linux libs                        Windows libs / libi
  ------              ----------                        -------------------
  tbb-rt              tbb-runtime/lib/libtbb.so.12      tbb-runtime/bin/tbb12.dll
                      depends: tbb-malloc,              libi: tbb-runtime/lib/tbb12.lib
                               tbb-malloc-proxy,        libi: tbb-runtime/lib/tbb.lib
                               tbb-bind                 depends: tbb-malloc,
                                                                  tbb-malloc-proxy,
                                                                  tbb-bind

  tbb-malloc          libtbbmalloc.so.2                 tbbmalloc.dll
                                                        libi: tbbmalloc.lib

  tbb-malloc-proxy    libtbbmalloc_proxy.so.2           tbbmalloc_proxy.dll
                                                        libi: tbb-devel/lib/tbbmalloc_proxy.lib

  tbb-bind            libtbbbind.so.3                   tbbbind.dll
                      libtbbbind_2_0.so.3               tbbbind_2_0.dll
                      libtbbbind_2_5.so.3               tbbbind_2_5.dll
                                                        libi: tbb-devel/lib/tbbbind.lib
                                                        libi: tbb-devel/lib/tbbbind_2_0.lib
                                                        libi: tbb-devel/lib/tbbbind_2_5.lib

  tbb-devel           tbb-runtime/lib/libtbb.so         (linux only - no Windows equivalent)
                      tbb-runtime/lib/libtbbmalloc.so
                      tbb-runtime/lib/libtbbmalloc_proxy.so
                      tbb-runtime/lib/libtbbbind_2_5.so
                      depends: tbb-rt

## Platform notes

- tbb-devel exists only on Linux; it provides the unversioned .so symlinks
  needed at link time. Windows links via import libs (.lib) instead.
- SONAME versions are stable across 2022.3.1 -> 2023.0.0:
    libtbb.so.12 / libtbbmalloc.so.2 / libtbbmalloc_proxy.so.2 / libtbbbind*.so.3
