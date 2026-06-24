# liboneapi-ifort - Intel Fortran Compiler (ifx/fpp) and runtime

> **NOTE:**  
This package is not open source and does not contain any source code. Instead,
in order to "build" the exported target(s) it downloads (potentially large)
pre-built binaries provided by Intel for the target platform.
>
> CI for this package is disabled due to the above.  
Supported platforms/compilers are Windows/MSVC and Linux.

This is a `build2` package for the [Intel oneAPI Fortran
Compiler](https://www.intel.com/content/www/us/en/developer/tools/oneapi/fortran-compiler.html)
C++ library. It provides the Fortran runtime libraries (libifcore, libifport)
for linking against Fortran-compiled objects, the ifx compiler driver, the fpp
Fortran preprocessor, and the xfortcom compiler frontend.


## Usage

To start using `liboneapi-ifort` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: liboneapi-ifort ^2026.0.0-
```

Then import the Fortran runtime for linking against Fortran-compiled code:

```
import libs = liboneapi-ifort%libs{ifort}
```

Or import the compiler as a build tool:

```
import! ifx = liboneapi-ifort%exe{ifx}
```


## Importable targets

This package provides the following importable targets:

```
libs{ifort}
exe{ifx}
exe{fpp}
exe{xfortcom}
```


## Configuration variables

This package provides the following configuration variables:

```
[dir_path] config.liboneapi_ifort.cache ?= $out_root
```

The directory used to cache downloaded binary archives between builds. If
`config.liboneapi.cache` is set (a shared project-wide cache directory), it
takes precedence over the per-package default of `$out_root`.
