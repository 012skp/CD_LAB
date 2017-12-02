default: 
	flex -o alex.c a.l
	bison -d -o aparse.c  a.y
	gcc  alex.c aparse.c  -ll -ly 
	./a.out
