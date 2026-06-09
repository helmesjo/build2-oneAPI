# liboneapi-ifort

## Versions

  Platform  Component ID                           Version
  --------  ------------                           -------
  linux     `intel.oneapi.lin.ifort-compiler`      2026.0.0+947  (devel only)
  windows   `intel.oneapi.win.ifort-compiler`      2026.0.0+944  (devel only)

Content manifest basename:
  linux:   `intel.oneapi.lin.compiler.content`
  windows: `intel.oneapi.win.compiler.content`

There is no separate runtime component; all files come from the devel package.

## Tarball layout

Tarballs extract under `_installdir/compiler/<ver>/` which maps to
`ifort-devel/` after the version-segment strip in `redist.build`.

### Linux  ->  `extract{ifort-devel}`

  ifort-devel/bin/fpp               - Fortran preprocessor
  ifort-devel/bin/ifx               - Intel Fortran Compiler driver
  ifort-devel/bin/ifx.cfg           - compiler config (not an exe target)
  ifort-devel/bin/compiler/xfortcom - backend compiler (subdirectory)

  ifort-devel/lib/libifcore.so      - Fortran core runtime
  ifort-devel/lib/libifcoremt.so    - thread-safe Fortran core runtime
  ifort-devel/lib/libifport.so      - Fortran portability library
  ifort-devel/lib/libicaf.so        - Coarray Fortran runtime (not in ifort-rt, see below)

## build2 targets

  Target       Description
  ------       -----------
  ifort-rt     Fortran runtime libraries (libifcore, libifcoremt, libifport)
  exe{ifx}     Intel Fortran Compiler driver
  exe{fpp}     Fortran preprocessor

`libicaf.so` (Coarray Fortran runtime) is not included in `ifort-rt` because it
has an undeclared dependency on MPI (`libmpi.so.12`).  It can be added once MPI
is packaged as a separate build2 package and declared as a dependency here.

## Usage

Link Fortran-compiled code against `libs{ifort-rt}`.

Import the compiler via:

  import! ifx = liboneapi-ifort%exe{ifx}
