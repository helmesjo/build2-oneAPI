# liboneapi-ifort

build2 package for the Intel Fortran Compiler Classic (`ifort`) and its
Fortran runtime libraries, sourced from the Intel oneAPI Toolkit.

## Importable targets

```
libs{ifort-rt}   Fortran runtime libraries (libifcore, libifport, etc.)
exe{ifx}         Intel Fortran Compiler driver
exe{fpp}         Fortran preprocessor
```

## Usage

Import the Fortran runtime for linking against Fortran-compiled code:

```
import rt = liboneapi-ifort%libs{ifort-rt}
```

Import the compiler as a build tool:

```
import! ifx = liboneapi-ifort%exe{ifx}
```
