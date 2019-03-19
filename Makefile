CFLAG = -c -Wall

link: dist/common_functions.o dist/simulate.o
	gcc dist/common_functions.o dist/simulate.o -o dist/simulate


dist/simulate.o: simulate.c
	gcc $(CFLAG) simulate.c -o dist/simulate.o

dist/common_functions.o: lib/common_functions.c 
	gcc $(CFLAG) lib/common_functions.c -o dist/common_functions.o

clean:
	rm -rf ./dist && mkdir dist
