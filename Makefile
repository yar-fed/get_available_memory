default: main

main:
	gcc -o $@.o $@.c

clean:
	rm *.o