# liboneapi-tbb

## Versions

  Platform  Component ID                       Version
  --------  ------------                       -------
  linux     intel.oneapi.lin.tbb.runtime       2023.0.0+724
  linux     intel.oneapi.lin.tbb.devel         2023.0.0+724
  windows   intel.oneapi.win.tbb.runtime       2023.0.0+716
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

Windows ships a separate `tbb.devel` extract alongside `tbb.runtime`.
Some import libs (`tbb12.lib`, `tbb.lib`) ship in the runtime tarball;
others (`tbbmalloc_proxy.lib`, `tbbbind*.lib`) ship in the devel tarball.

## build2 targets

  Target              Linux libs                        Windows libs / libi
  ------              ----------                        -------------------
  tbb                 tbb-runtime/lib/libtbb.so.12.18   tbb-runtime/bin/tbb12.dll
                                                        libi: tbb-runtime/lib/tbb12.lib
                                                        libi: tbb-runtime/lib/tbb.lib

  tbb-malloc          libtbbmalloc.so.2.18              tbbmalloc.dll
                                                        libi: tbbmalloc.lib

  tbb-malloc-proxy    libtbbmalloc_proxy.so.2.18        tbbmalloc_proxy.dll
                      depends: tbb-malloc               libi: tbb-devel/lib/tbbmalloc_proxy.lib
                                                        depends: tbb-malloc

  tbb-bind            libtbbbind.so.3.18                tbbbind.dll
                      libtbbbind_2_0.so.3.18            tbbbind_2_0.dll
                      libtbbbind_2_5.so.3.18            tbbbind_2_5.dll
                                                        libi: tbb-devel/lib/tbbbind.lib
                                                        libi: tbb-devel/lib/tbbbind_2_0.lib
                                                        libi: tbb-devel/lib/tbbbind_2_5.lib

## Platform notes

- The real ELF filenames carry a two-part version (e.g. libtbb.so.12.18) that
  changes with each upstream release. The SONAME embedded in each ELF uses only
  the major part (libtbb.so.12) and is stable within a major version. Update the
  package.json lib paths when upgrading to a new upstream release.
