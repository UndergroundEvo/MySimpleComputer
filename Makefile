<<<<<<< HEAD
.PHONY: all clean

app_name = sc
lib_name = mySimpleComputer
obj_folder = obj
=======
lib1 = mySimpleComputer
lib2 = myTerm
>>>>>>> lab02

cflags = -Wall -I include -MP -MMD

objects_temp = $(shell find src/ -name '*.c')
objects = $(objects_temp:%.c=obj/%.o)

libs_temp = $(shell find src/lib/ -name '*.c')
libs = $(libs_temp:src/lib/%.c=obj/src/lib/lib%.a)

<<<<<<< HEAD
all: $(app_path)

$(app_path): $(app_objects) $(lib_path)
	mkdir -p bin/
	gcc $(cflags) $(myflag) -Lobj/src/$(lib_name) $< -l$(lib_name) -o $@

$(lib_path): $(lib_objects)
=======
.PHONY: all
all: create_dirs $(objects) $(libs)
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/main.o -l$(lib1) -l$(lib2)  -o bin/main
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/lab01.o -l$(lib1) -l$(lib2) -o bin/lab01
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/lab02.o -l$(lib1) -l$(lib2) -o bin/lab02

obj/src/lib/lib%.a: obj/src/lib/%.o
>>>>>>> lab02
	ar rcs $@ $^

obj/%.o: %.c
	gcc -c $(cflags) $< -o $@

create_dirs:
	mkdir -p bin/
	mkdir -p obj/src/main/
	mkdir -p obj/src/lib/

clean:
	rm -rf obj
	rm -rf bin