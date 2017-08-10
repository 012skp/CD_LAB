default: driver

libcdlab.a: lexical.cc lexical.h
	g++ -c lexical.cc -I.
	ar -rcs libcdlab.a -o lexical.o
	rm lexical.o
driver: libcdlab.a driver_program.cc
	g++ driver_program.cc -o driver -L. -lcdlab

clean:
	rm -f *.o *.a driver
