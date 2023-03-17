main_app = main_app
lab1_test = lab01
lab2_test = lab02
lib_name = mySimpleComputer
obj_folder = obj

cflags = -Wall -Werror -I include -MP -MMD
# cflags += -lm

main_app_path = bin/$(main_app)
lab1_test_path = bin/$(lab1_test)
lab2_test_path = bin/$(lab2_test)

lib_path = obj/src/$(lib_name)/lib$(lib_name).a

main_app_sources = src/sc/$(main_app).c
main_app_objects = $(main_app_sources:src/%.c=obj/src/%.o)
lab1_test_sources = src/sc/$(lab1_test).c
lab1_test_objects = $(lab1_test_sources:src/%.c=obj/src/%.o)
lab2_test_sources = src/sc/$(lab2_test).c
lab2_test_objects = $(lab2_test_sources:src/%.c=obj/src/%.o)

lib_sources = $(shell find src/$(lib_name) -name '*.c')
lib_objects = $(lib_sources:src/%.c=obj/src/%.o)

.PHONY: all
all: $(main_app_objects) $(lab1_test_objects) $(lab2_test_objects) $(lib_path)
	mkdir -p bin/
	gcc $(cflags) -Lobj/src/mySimpleComputer/ $(main_app_objects) -lmySimpleComputer -o $(main_app_path)
	gcc $(cflags) -Lobj/src/mySimpleComputer/ $(lab1_test_objects) -lmySimpleComputer -o $(lab1_test_path)
	gcc $(cflags) -Lobj/src/mySimpleComputer/ $(lab2_test_objects) -lmySimpleComputer -o $(lab2_test_path)

$(lib_path): $(lib_objects)
	ar rcs $@ $^

obj/%.o: %.c
	mkdir -p obj/src/sc/
	mkdir -p obj/src/mySimpleComputer/
	gcc -c $(cflags) $< -o $@

.PHONY: clean
clean:
	rm -r obj
	rm -r bin