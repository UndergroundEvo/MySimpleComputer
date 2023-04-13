lib1 = mySimpleComputer
lib2 = myTerm
lib3 = myBigChars

cflags = -Wall -I include -MP -MMD

objects_temp = $(shell find src/ -name '*.c')
objects = $(objects_temp:%.c=obj/%.o)

libs_temp = $(shell find src/lib/ -name '*.c')
libs = $(libs_temp:src/lib/%.c=obj/src/lib/lib%.a)

.PHONY: all
all: create_dirs $(objects) $(libs)
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/main.o -l$(lib1) -l$(lib2) -l$(lib3) -o bin/main
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/lab03.o -l$(lib1) -l$(lib2) -l$(lib3) -o bin/lab03
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/lab01.o -l$(lib1) -o bin/lab01
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/lab02.o -l$(lib1) -l$(lib2) -o bin/lab02

obj/src/lib/lib%.a: obj/src/lib/%.o
	ar rcs $@ $^

obj/%.o: %.c
	gcc -c $(cflags) $< -o $@

create_dirs:
	mkdir -p bin/
	mkdir -p obj/src/main/
	mkdir -p obj/src/lib/

.PHONY: clean
clean:
	rm -rf obj
	rm -rf bin