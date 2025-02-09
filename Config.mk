cflags := $(shell pkg-config --cflags --libs SDL2_ttf)
srend_src := $(wildcard src/*.c)
srend_obj := $(patsubst src/%.c,out/%.o,${srend_src})
srend_inc := $(wildcard include/*.h)
srend_preclude := -Iinclude