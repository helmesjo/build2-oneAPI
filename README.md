# oneAPI - build2 amalgamation of the Intel oneAPI family

> **NOTE:**  
These packages are not open source and do not contain any source code. Instead,
in order to "build" the exported target(s) they download (potentially large)
pre-built binaries provided by Intel for the target platform.
>
> CI for these packages are disabled due to the above.  
Supported platforms/compilers are Windows/MSVC & Linux. MacOS is (officially)
not supported.

`oneAPI` is a build2 amalgamation of packages for Intel oneAPI components
(proprietary only), enabling unified programming across heterogeneous
architectures.

Note that currently only this is included:
- oneMKL (Math Kernel Library)

These (proprietary only) should be added next:
- DPC++/C++ Compiler + runtime
- Fortran Compiler
- MPI Library
- IPP (Integrated Performance Primitives)
- VTune Profiler

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`oneAPI` libraries/tools in your `build2`-based project, then instead
see the official [documentation](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit.html).

The development setup for `oneAPI` uses the standard `bdep`-based workflow.
For example:

```
git clone https://github.com/build2-packaging/oneAPI.git
cd oneAPI

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```

# Locating Package URLs

1. Download & run the [offline installer](https://www.intel.com/content/www/us/en/developer/tools/oneapi/oneapi-toolkit-download.html?packages=oneapi-toolkit&oneapi-toolkit-os=linux&oneapi-lin=offline).
2. In the installation directory, located the `installer.install.intel...log` file,
   and in that file locate the `installer --log-dir` path:
    ```
    05/04/2026 19:06:37:773 : 22948 : MESSAGE : C:\Program Files (x86)\Intel\oneAPI\Installer\installer.exe is run with arguments: --log-dir C:/Users/me/AppData/Local/Temp/intel_oneapi_installer/2026.05.04.19.06.30.360
    ```
3. In the log directory, locate `installer...log` file and search for
   `https://installer.repos.intel.com/oneapi`.
