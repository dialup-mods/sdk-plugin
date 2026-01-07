<h1 align="center">🌐 Dial-Up Unreal Engine SDK Plugin 🌐</h1>
<p align="center">*Best viewed in 800x600*</p>

Build your generated SDK into a reusable library that can be safely shared across multiple plugins.

## Synopsis

```c++
#include "SDK.h"

Runtime::create();

// one time, from any plugin
Runtime::setFNameEntries(reinterpret_cast<TArray<FNameEntry*>*>(fNameEntriesAddr));
Runtime::setUObjects(reinterpret_cast<TArray<UObject*>*>(uObjectsAddr));

// anywhere, across all of your plugins
auto* objectClass = Runtime::findClass("Class Core.Object");
if (objectClass && objectClass->GetFullName() == "Class Core.Object") {
    printf("pass\n");
} else {
    printf("fail\n");
}
```

## Why?

Without this, every plugin compiles its own copy of the SDK:
- Duplicate symbols across plugins
- Multiple Runtime instances (cache duplication)
- ODR violations
- Heap corruption risks

**With DialUp-SDK:**
- ✓ One shared SDK lib
- ✓ Single Runtime instance
- ✓ Compile SDK once, link everywhere
- ✓ Type safety across boundaries

## Quick Start

### 1. Prerequisites

#### Install Dependencies

Run the following in Powershell as administrator to install: Git, CMake, Ninja, Clang, MSYS2

```powershell
iwr -useb https://raw.githubusercontent.com/dialup-mods/dialup/main/tools/install_build_deps.ps1 | iex
```

#### Clone and Install Build Tools
```bash
git clone --recursive git@github.com:dialup-mods/dialup.git
cd dialup
make install-tools
```

#### Generate your SDK

[Click here](https://github.com/dialup-tools/sdk-generator/README.md) to view the `Quick Start` section for the **Dial-Up SDK Generator**

### 2. Convert the generated SDK into a library
```sh
cd ../sdk-plugin
make configure
make build
make install
```

## Integration

### CMake (Recommended)
```cmake
find_package(DialUp-SDK REQUIRED PATHS $ENV{LOCALAPPDATA}/DialUp/sdk-plugin)
target_link_libraries(YourPlugin PRIVATE DialUp-SDK::DialUp-SDK)
```

Note: Use the code found in `test/test_Runtime.h` as an example

### Visual Studio
Integration with .vcxproj files is possible but our team finds it needlessly 
complex so it's undocumented. If you decide to go this route, we would love your
help and will gladly accept a PR to document the process :)

Note: vcpkg uses CMake under the hood anyway.

<details>
<summary>For the determined...</summary>

You'll need to configure:
- Headers: `~/AppData/Local/DialUp/sdk-plugin/include`
- DLL: `~/AppData/Local/DialUp/sdk-plugin/bin/DialUp-SDK.dll`
- Import lib: `~/AppData/Local/DialUp/sdk-plugin/bin/DialUp-SDK.lib`

</details>

## Testing

A `Runtime` test is provided in `test/`

To run the test:

- implement your function for finding the address of UObjects and FNameEntries in test_Runtime.h

- Run your game (tooling is currently set up for Rocket League, see: dialup/tooling/build-tools/. Simple change. Configuration options are under construction)

- Install the **Dial-Up Injector** \[[link](https://github.com/dialup-mods/injector)\]

- From the `/test` directory:

```sh
make configure
make build
make run
```

