default:
	flex -o symbol_tl.c symbol_t.l
	bison -d -o symbol_ty.c symbol_t.y
	gcc symbol_ty.c symbol_tl.c ch3hdr.c -ll -ly
	./a.out
