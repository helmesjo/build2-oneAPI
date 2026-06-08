# intel-oneapi packaging notes

## Packages

  [liboneapi-compilers-common/DEV-README.md](liboneapi-compilers-common/DEV-README.md) - Compiler common runtime (libimf, libsvml, libintlc)
  [liboneapi-mkl/DEV-README.md](liboneapi-mkl/DEV-README.md)                         - MKL targets, layout, platform notes
  [liboneapi-openmp/DEV-README.md](liboneapi-openmp/DEV-README.md)                   - OpenMP targets, layout, platform notes
  [liboneapi-tbb/DEV-README.md](liboneapi-tbb/DEV-README.md)                         - TBB targets, layout, platform notes

## Download mechanism

`redist.build` implements a three-step download per component:

  1. Fetch content manifest JSON from Intel CDN:
       {baseUrl}/{subdir}/{basename}{verSuffix}{version}.ext
     e.g. https://installer.repos.intel.com/oneapi/mkl/lin/
            intel.oneapi.lin.onemkl.content,v=2026.0.0+908.json

  2. Each package's `manifest.json` names its components explicitly via
     `runtime_id` (and `devel_id` where applicable). Parse the content
     manifest's `packages[]` array to find the entry whose ID ends with
     the given `runtime_id` or `devel_id`, then fetch that component's
     `manifest.json`.

  3. From the component `manifest.json`, locate `cupPayload.cup` and
     download it (cached as a `.tar` in `$out_root/`).

  4. Extract with `bsdtar`, stripping the path prefix up to and including
     the version segment:
       _installdir/<component>/<ver>/<rest>  ->  <extract-name>/<rest>

## Content manifest basenames

  Package             linux                                windows
  -------             -----                                -------
  mkl                 intel.oneapi.lin.onemkl.content      intel.oneapi.win.onemkl.content
  tbb                 intel.oneapi.lin.tbb_oneapi.content  intel.oneapi.win.tbb_oneapi.content
  openmp              intel.oneapi.lin.compiler.content    intel.oneapi.win.compiler.content
  compilers-common    intel.oneapi.lin.compiler.content    intel.oneapi.win.compiler.content

## Updating to a new release

The only field that changes per release in each package's `manifest.json` is
`version` (e.g. `2026.0.0+908`). The `+build` suffix is not derivable from
the upstream version alone; the installer must be run once to fetch it.

### Step 1: obtain the offline installer

Download the offline installer from:
  https://www.intel.com/content/www/us/en/developer/tools/oneapi/oneapi-toolkit-download.html

Select: Intel oneAPI Toolkit - Linux or Windows - Offline Installer.

This produces intel-oneapi-toolkit-20YY.X.Y.Z.BUILD_offline.sh on Linux
and intel-oneapi-toolkit-20YY.X.Y.Z.BUILD_offline.exe on Windows.

### Step 2: list components

Run the appropriate command for the target platform. Both produce the same
tabular output: component ID, version+build string, installed flag, and name.

Linux - install.sh is a thin wrapper around the bootstrapper binary:

  Get all component IDs and version+build numbers (queries CDN, no install):
    ./install.sh --list-components

  --list-components downloads the package manager (~10 MB) but not the
  component payloads, and prints every component ID with its exact
  version+build string.

  Other useful bootstrapper flags:

    Download payloads without installing (requires EULA acceptance):
      ./install.sh -s --action downloadonly --eula accept \
        --components <id>:<id>:... \
        --download-dir <dir>

    --download-cache <dir>   where to store the package manager cache
    --proxy <url>            proxy support if needed

Windows - use the offline installer exe. The outer exe requires elevation.
Run from an administrator cmd.exe prompt:

    intel-oneapi-toolkit-YYYY.N.N.BBB_offline.exe --silent --a --list-components

  The output format is identical to the Linux bootstrapper output.

### Step 3: update manifest.json

Match the listed component IDs against the per-package DEV-READMEs to find
the relevant version+build strings. Update the `version` field in each
`manifest.json` accordingly.

  Package                  Windows component ID                        Linux component ID
  -------                  --------------------                        ------------------
  liboneapi-mkl            intel.oneapi.win.mkl.devel                  intel.oneapi.lin.mkl.devel
                           intel.oneapi.win.mkl.runtime                intel.oneapi.lin.mkl.runtime
  liboneapi-tbb            intel.oneapi.win.tbb.devel                  intel.oneapi.lin.tbb.devel
                           intel.oneapi.win.tbb.runtime                intel.oneapi.lin.tbb.runtime
  liboneapi-openmp         intel.oneapi.win.openmp                     intel.oneapi.lin.openmp
  liboneapi-compilers-     intel.oneapi.win.compilers-common           intel.oneapi.lin.compilers-common
    common                 intel.oneapi.win.compilers-common-runtime   intel.oneapi.lin.compilers-common.runtime

Note: `compilers-common` uses a hyphen before `runtime` on Windows
(`compilers-common-runtime`) but a dot on Linux (`compilers-common.runtime`).
This naming inconsistency is why all packages now use explicit `runtime_id`
and `devel_id` fields in `manifest.json` rather than relying on suffix
matching.

Also update the Versions table in each package's DEV-README.md to record the
verified version+build strings.

### Probing for libs, libi, and liba

After `bdep update` has extracted the component tarballs, run these commands
from the project root to discover what files belong under each package.json
key. Replace the example path with the appropriate package out_base.

Linux:

  Shared libraries (libs):

    `find ../intel-oneapi-toolkit-gcc/liboneapi-mkl/mkl -name "*.so*" ! -type l | sort`

  Static archives (liba):

    `find ../intel-oneapi-toolkit-gcc/liboneapi-mkl/mkl -name "*.a" | sort`

Windows (VS Developer Command Prompt):

  Shared libraries (libs - DLLs):

    `dir /s /b ..\intel-oneapi-toolkit-msvc\liboneapi-mkl\mkl\*.dll | sort`

  All .lib files (libi or liba, needs classification):

    `dir /s /b ..\intel-oneapi-toolkit-msvc\liboneapi-mkl\mkl\*.lib | sort`

  Classify each .lib (.obj members => liba, otherwise libi).
  Output sorted: liba first, then libi:

    `(for /r ..\intel-oneapi-toolkit-msvc\liboneapi-mkl\mkl %f in (*.lib) do @(dumpbin /ARCHIVEMEMBERS "%f" 2>nul | findstr /c:".obj" >nul && echo liba: %f || echo libi: %f)) | sort`
