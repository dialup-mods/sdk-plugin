# DialUp SDK Plugin

Build your generated SDK into a reusable library that can be safely shared across multiple plugins.

## Why?

Without this, every plugin compiles its own copy of the SDK:
- Duplicate symbols across plugins
- Multiple Runtime instances (cache duplication)
- ODR violations
- Heap corruption risks

**With DialUp-SDK:**
- ✅ One shared SDK lib
- ✅ Single Runtime instance
- ✅ Compile SDK once, link everywhere
- ✅ Type safety across boundaries


## Building

First, clone from the [main DialUp repo](https://github.com/dialup-mods/dialup)

```sh
git clone git@github.com:dialup-mods/dialup.git
cd dialup
```

Install build dependencies

```cmd
# install the latest CMake, Ninja, Clang, Git, and MSYS2 via handy script
powershell -ExecutionPolicy Bypass -File install_build_deps.ps1
```

Install DialUp build tools

```sh
make install-tools
```

Generate your SDK

```sh
cd sdk-generator
make configure game=mygame # (or `make configure` to use the default profile)
make build
make inject
```

Now convert the generated SDK into a library
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

Note: Use the code found in test/ as an example

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

### Usage

```c++
#include "SDK.h"

Runtime::create();

// one time, from any plugin
Runtime::setFNameEntries(reinterpret_cast<TArray<FNameEntry*>*>(fNameEntriesAddr));
Runtime::setUObjects(reinterpret_cast<TArray<UObject*>*>(uObjectsAddr));

// anywhere, across all of your plugins
auto* uObjCls = Runtime::findClass("Class Core.Object");
if (uObjCls && uObjCls->GetFullName() == "Class Core.Object") {
    printf("pass\n");
} else {
    printf("fail\n");
}
```
