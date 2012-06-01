all: main
main: main.o translatable.o type.o dtdfile.o
	gcc main.o translatable.o type.o dtdfile.o -o main `pkg-config --cflags --libs gobject-2.0`
main.o: main.c translatable.h dtdfile.h
	gcc -c main.c -o main.o `pkg-config --cflags gobject-2.0`
translatable.o: translatable.c type.h translatable.h
	gcc -c translatable.c -o translatable.o `pkg-config --cflags gobject-2.0`
type.o: type.c type.h
	gcc -c type.c -o type.o `pkg-config --cflags gobject-2.0`
dtdfile.o: dtdfile.c dtdfile.h type.h
	gcc -c dtdfile.c -o dtdfile.o `pkg-config --cflags gobject-2.0`
clean:
	rm *.o
