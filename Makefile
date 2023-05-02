<<<<<<< HEAD
<<<<<<< HEAD
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
=======
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
>>>>>>> origin/lab03
	rm -rf bin
=======
lib0 = Render
lib1 = mySimpleComputer
lib2 = myTerm
lib3 = myBigChars
lib4 = myReadkey

cflags = -Wall -I include -MP -MMD

objects_temp = $(shell find src/ -name '*.c')
objects = $(objects_temp:%.c=obj/%.o)

libs_temp = $(shell find src/lib/ -name '*.c')
libs = $(libs_temp:src/lib/%.c=obj/src/lib/lib%.a)

.PHONY: all
all: create_dirs $(objects) $(libs) bin/main bin/lab01 bin/lab02 bin/lab03 bin/lab04

-include obj/src/lib/*.d
-include obj/src/main/*.d

obj/src/lib/lib%.a: obj/src/lib/%.o
	ar rcs $@ $^

obj/%.o: %.c
	gcc -c $(cflags) $< -o $@

create_dirs:
	mkdir -p bin/
	mkdir -p obj/src/main/
	mkdir -p obj/src/lib/
	touch create_dirs

bin/main:
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/main.o -l$(lib0) -l$(lib1) -l$(lib2) -l$(lib3) -l$(lib4) -o bin/main

bin/lab01:
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/lab01.o -l$(lib1) -o bin/lab01

bin/lab02:
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/lab02.o -l$(lib1) -l$(lib2) -o bin/lab02

bin/lab03:
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/lab03.o -l$(lib1) -l$(lib2) -l$(lib3) -o bin/lab03

bin/lab04:
	gcc $(cflags) -Lobj/src/lib/ obj/src/main/lab04.o -l$(lib1) -l$(lib2) -l$(lib3) -l$(lib4) -o bin/lab04

.PHONY: clean
clean:
	rm -f create_dirs
	rm -rf obj
	rm -rf bin
>>>>>>> lab04
