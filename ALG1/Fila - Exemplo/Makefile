objects = main.o fila.o

main : $(objects)
		gcc -o main $(objects)

fila.o : fila.h
main.o: fila.h

clean :
		rm *.o main