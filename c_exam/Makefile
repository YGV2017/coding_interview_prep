CC = gcc
CPPFLAGS ?=
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -g
LDFLAGS ?=
LDLIBS ?=
TIMEOUT ?= timeout 15s
BLOCKS := block1 block3 block7
BUILD_DIR ?= build
HEADERS := $(wildcard include/*.h)

.PHONY: all test test-solutions sanitize clean $(addprefix test-,$(BLOCKS)) FORCE
all: $(addprefix $(BUILD_DIR)/exercises/test_,$(BLOCKS))

test: $(addprefix test-,$(BLOCKS))

$(addprefix test-,$(BLOCKS)): test-%: $(BUILD_DIR)/exercises/test_%
	$(TIMEOUT) ./$<

test-solutions: $(addprefix $(BUILD_DIR)/solutions/test_,$(BLOCKS))
	@set -e; for block in $(BLOCKS); do $(TIMEOUT) ./$(BUILD_DIR)/solutions/test_$$block; done

# Always rebuild so compiler flag changes are respected.
$(BUILD_DIR)/exercises/test_%: tests/test_%.c exercises/%.c $(HEADERS) FORCE
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -Iinclude $(CFLAGS) -UNDEBUG $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) $(if $(filter test_block7,$(@F)),-pthread) -o $@

$(BUILD_DIR)/solutions/test_%: tests/test_%.c solutions/%.c $(HEADERS) FORCE
	@mkdir -p $(@D)
	$(CC) $(CPPFLAGS) -Iinclude $(CFLAGS) -UNDEBUG $(filter %.c,$^) $(LDFLAGS) $(LDLIBS) $(if $(filter test_block7,$(@F)),-pthread) -o $@

sanitize:
	$(MAKE) BUILD_DIR=build/sanitize CFLAGS="$(CFLAGS) -fsanitize=address,undefined -fno-omit-frame-pointer" test-solutions

clean:
	rm -rf build
