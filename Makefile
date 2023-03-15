app_name = sc
lib_name = mySimpleComputer
obj_folder = obj

cflags = -Wall -Werror -I include -MP -MMD
# cflags2 = -Wall -Werror
# myflag = -lm

app_path = bin/$(app_name)
lib_path = obj/src/$(lib_name)/lib$(lib_name).a

app_sources = $(shell find src/$(app_name) -name '*.c')
app_objects = $(app_sources:src/%.c=obj/src/%.o)

lib_sources = $(shell find src/$(lib_name) -name '*.c')
lib_objects = $(lib_sources:src/%.c=obj/src/%.o)

# test_name = test
# test_path = bin/$(test_name)

# test_sources = $(shell find test/ -name '*.c')
# test_objects = $(test_sources:test/%.c=obj/test/%.o)

.PHONY: all
all: $(app_path)

$(app_path): $(app_objects) $(lib_path)
	mkdir -p bin/
	gcc $(cflags) $(myflag) -Lobj/src/mySimpleComputer/ $< -lmySimpleComputer -o $@

$(lib_path): $(lib_objects)
	ar rcs $@ $^

obj/%.o: %.c
	mkdir -p obj/src/sc/
	mkdir -p obj/src/mySimpleComputer/
	gcc -c $(cflags) $< $(myflag) -o $@

# .PHONY: test
# test: $(test_path)

# $(test_path): $(test_objects) $(lib_path)
# 	gcc $(cflags) -I thirdparty -I src $^ $(myflag) -o $@

.PHONY: clean
clean:
	$(RM) $(app_path) $(lib_path)
	rm -r obj
	rm -r bin
	find obj/ -name '*.o' -exec $(RM) '{}' \;
	find obj/ -name '*.i' -exec $(RM) '{}' \;
	find obj/ -name '*.d' -exec $(RM) '{}' \;
