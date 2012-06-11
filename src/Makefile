all: test1 test2
test1: test1.o translatable.o filetype.o propertiesfiletype.o localestring.o hashvalue.o
	gcc test1.o translatable.o filetype.o propertiesfiletype.o localestring.o hashvalue.o -o test1 `pkg-config --cflags --libs gobject-2.0`
test1.o: test1.c translatable.h dtdfiletype.h
	gcc -c test1.c -o test1.o `pkg-config --cflags gobject-2.0`

test2: test2.o translatable.o filetype.o propertiesfiletype.o localestring.o hashvalue.o
	gcc test2.o translatable.o filetype.o propertiesfiletype.o localestring.o hashvalue.o -o test2 `pkg-config --cflags --libs gobject-2.0`
test2.o: test2.c translatable.h dtdfiletype.h
	gcc -c test2.c -o test2.o `pkg-config --cflags gobject-2.0`

translatable.o: translatable.c filetype.h translatable.h hashvalue.h
	gcc -c translatable.c -o translatable.o `pkg-config --cflags gobject-2.0`
filetype.o: filetype.c filetype.h
	gcc -c filetype.c -o filetype.o `pkg-config --cflags gobject-2.0`
dtdfiletype.o: dtdfiletype.c dtdfiletype.h filetype.h
	gcc -c dtdfiletype.c -o dtdfiletype.o `pkg-config --cflags gobject-2.0`
propertiesfiletype.o: propertiesfiletype.c propertiesfiletype.h filetype.h
	gcc -c propertiesfiletype.c -o propertiesfiletype.o `pkg-config --cflags gobject-2.0`
hashvalue.o: hashvalue.c hashvalue.h localestring.h
	gcc -c hashvalue.c -o hashvalue.o `pkg-config --cflags gobject-2.0`
localestring.o: localestring.c localestring.h
	gcc -c localestring.c -o localestring.o `pkg-config --cflags gobject-2.0`
clean:
	rm -f *.o test1 test2
