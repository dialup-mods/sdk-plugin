LOCALAPPDATA := $(shell powershell -NoProfile -Command "[Environment]::GetFolderPath('LocalApplicationData')")
DIALUP_ROOT := $(LOCALAPPDATA)/DialUp
BUILD_DIR  := build
DLL        := AllTests.dll

include $(DIALUP_ROOT)/build-tools/common.mk
include $(DIALUP_ROOT)/build-tools/shell.mk
include $(DIALUP_ROOT)/build-tools/rocketleague.mk

.PHONY: configure build run clean

configure: check-shell
	@echo "🛠️ Configuring CMake..."
	$(call run_with_vcvars, cmake -S . -B build -G $(GENERATOR) -DCMAKE_BUILD_TYPE=RelWithDebInfo $(ARGS))

build: configure
	$(call run_with_vcvars, cmake --build build --config RelWithDebInfo $(ARGS))

run:
	# copy to RL bin dir, run, remove
	@bash -lc 'cp -v "$(BUILD_DIR)/$(DLL)" "$(binary_dir)/$(DLL)"'
	"$(INJECTOR)" "$(target)" "$(SDK_DLL)"
	"$(INJECTOR)" "$(target)" "$(DLL)"

clean:
	@rm -rf build
