main: main.o Cow.o Farm.o
	g++ main.o Cow.o Farm.o -o main

main.o: main.cpp
	g++ -c main.cpp -o main.o

Cow.o: Cow.cpp Cow.h
	g++ -c Cow.cpp -o cow.o

Farm.o: Farm.cpp Farm.h
	g++ -c Farm.cpp -o farm.o

clean: 
	rm -f *.o -f main