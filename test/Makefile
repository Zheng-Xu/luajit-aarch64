# Default values for running luajit.
LUAJIT?=luajit
LUA_FLAGS?=-jdump=+rsXa
# Define tests which should be skipped for some reasons.
SKIPPED_LUA_TEST=fpm_cos addov
# mul and div on x86 fail due to issue with XCFLAGS="-DLUAJIT_ENABLE_GC64"
SKIPPED_LUA_TEST_x86_64=mul div
SKIPPED_LUA_TEST_i686=mul div
# Below features have not been implemented on aarch64.
SKIPPED_LUA_TEST_aarch64=div call_vararg cnew cnewi xstore_addvalue mod fref href newref

# Find all tests inside the folder.
LUA_TEST_SRC=$(wildcard *.lua)
ALL_LUA_TEST=$(LUA_TEST_SRC:%.lua=test_%)

# Define the tests.
ARCH=$(shell uname -m)
ALL_SKIPPED_LUA_TEST=$(SKIPPED_LUA_TEST) $(SKIPPED_LUA_TEST_$(ARCH))
DISABLED_LUA_TEST:=$(ALL_SKIPPED_LUA_TEST:%=test_%)
ENABLED_LUA_TEST=$(filter-out $(DISABLED_LUA_TEST),$(ALL_LUA_TEST))


test: $(ENABLED_LUA_TEST)

skipped:
	success= ; \
	failed= ; \
	for t in $(ALL_SKIPPED_LUA_TEST) ; do \
	  echo "$(LUAJIT) $(LUA_FLAGS) $$t.lua" ; \
	  if $(LUAJIT) $(LUA_FLAGS) $$t.lua ; then \
	    success="$$success $$t" ; \
	  else \
	    failed="$$failed $$t" ; \
	  fi \
	done ; \
	echo "SUCCESS : $$success" ; \
	echo "FAILED : $$failed"

$(ALL_LUA_TEST) : test_% : %.lua
	@echo "Running test : $@"
	$(LUAJIT) $(LUA_FLAGS) $<

.PHONY: $(ALL_LUA_TEST)
