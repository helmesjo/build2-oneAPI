# liboneapi-mpi

## Versions

  Platform  Component ID                        Version
  --------  ------------                        -------
  linux     `intel.oneapi.lin.mpi.devel`        2021.18.0+745
  linux     `intel.oneapi.lin.mpi.runtime`      2021.18.0+745
  windows   `intel.oneapi.win.mpi.devel`        2021.18.0+740
  windows   `intel.oneapi.win.mpi.runtime`      2021.18.0+740

Content manifest basename:
  linux:   `intel.oneapi.lin.mpi_oneapi.content`
  windows: `intel.oneapi.win.mpi_oneapi.content`

Both devel and runtime components are required. Headers and import libraries
come from devel; shared libraries, executables, and legal files come from
runtime.

## Tarball layout

Tarballs extract under `_installdir/mpi/<ver>/` which maps to `mpi-devel/` or
`mpi-runtime/` after the version-segment strip in `redist.build`.

### Windows  ->  `extract{mpi-devel}`

  mpi-devel/include/mpi.h          - main MPI C header
  mpi-devel/include/mpi_abi.h      - ABI-stable interface header
  mpi-devel/include/mpicxx.h       - C++ bindings header
  mpi-devel/include/mpif.h         - Fortran bindings header
  mpi-devel/include/mpio.h         - MPI I/O header
  mpi-devel/include/mpiof.h        - MPI I/O Fortran header

  mpi-devel/lib/impi.lib           - libi (import library for impi.dll)
  mpi-devel/lib/impicxx.lib        - liba (static C++ bindings archive)
  mpi-devel/lib/libmpi_ilp64.lib   - ILP64 import library (not packaged)
  mpi-devel/lib/mpi_abi.lib        - ABI-stable import library (not packaged)

### Windows  ->  `extract{mpi-runtime}`

  mpi-runtime/bin/impi.dll         - MPI shared library (DLL)
  mpi-runtime/bin/mpiexec.exe      - job launcher
  mpi-runtime/bin/impi_info.exe    - runtime diagnostic tool

  mpi-runtime/share/doc/mpi/license.txt
  mpi-runtime/share/doc/mpi/third-party-programs.txt

### Linux  ->  `extract{mpi-devel}` and `extract{mpi-runtime}`

  (similar structure; DLLs become .so files, no import libraries)

  mpi-runtime/lib/libmpi.so
  mpi-runtime/lib/libmpicxx.so
  mpi-runtime/lib/libmpifort.so

## build2 targets

  Target      Linux libs                      Windows libs / libi
  ------      ----------                      -------------------
  mpi         libmpi.so                       impi.dll / impi.lib
  mpicxx      libmpicxx.so                    (Linux only)
  mpifort     libmpifort.so                   (Linux only)

  exe{mpiexec}   bin/mpiexec    bin/mpiexec.exe
  exe{impi_info} bin/impi_info  bin/impi_info.exe

The `.exe` extension is omitted from `package.json`. The buildfile assigns it
on Windows via `$name-runtime/bin/exe{*}: extension = exe`.

Legal files are under `share/doc/mpi/` in the runtime extract (no `licensing/`
subdirectory, unlike some other oneAPI packages).

## Usage

Link against `libs{mpi}` to use Intel MPI in C programs. On Linux,
`libs{mpicxx}` and `libs{mpifort}` are available for C++ and Fortran
programs respectively.

Import the job launcher and diagnostic tool via:

  import! mpiexec   = liboneapi-mpi%exe{mpiexec}
  import! impi_info = liboneapi-mpi%exe{impi_info}
