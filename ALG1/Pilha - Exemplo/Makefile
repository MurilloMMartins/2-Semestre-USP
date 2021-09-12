objects = pilha.o main.o

teste : $(objects)
	gcc -o teste $(objects)

pilha.o : pilha.h
main.o: pilha.h

clean :
	rm *.o teste