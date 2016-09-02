
OPTIONS = -std=c90 -pedantic -Wall -Werror

sort.out: sort.o ListImplementation.o
	gcc $(OPTIONS) sort.o ListImplementation.o -o sort.out

test.out: test.o ListImplementation.o
	gcc $(OPTIONS) test.o ListImplementation.o -o test.out

sort.o: sort.c ListInterface.h ListType.h
	gcc $(OPTIONS) -c sort.c

test.o: test.c ListInterface.h ListType.h
	gcc $(OPTIONS) -c test.c

ListImplementation.o: ListImplementation.c ListInterface.h ListType.h
	gcc $(OPTIONS) -c ListImplementation.c

clean:
	rm *.o test.out


















