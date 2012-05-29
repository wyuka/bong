all: main
main: main.o translatable.o type.o
	gcc main.o translatable.o type.o -o main `pkg-config --cflags --libs glib-2.0`
main.o: main.c translatable.h
	gcc -c main.c -o main.o `pkg-config --cflags --libs glib-2.0`
translatable.o: translatable.c type.h translatable.h
	gcc -c translatable.c -o translatable.o `pkg-config --cflags --libs glib-2.0`
type.o: type.c type.h
	gcc -c type.c -o type.o `pkg-config --cflags --libs glib-2.0`
