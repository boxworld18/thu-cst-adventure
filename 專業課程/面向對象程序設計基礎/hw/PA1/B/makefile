#2020010869

.PHONY: main f1.o f2.o f3.o f4.o main.o

include control.mak

ifeq (TRUE, $(F1)) 
val1 = -D__F1__
f1o = f1.o
else
val1 =
f1o =
endif

ifeq (TRUE, $(F2)) 
val2 = -D__F2__
f2o = f2.o
else
val2 =
f2o =
endif

ifeq (TRUE, $(F3)) 
val3 = -D__F3__
f3o = f3.o
else
val3 =
f3o =
endif

ifeq (TRUE, $(F4)) 
val4 = -D__F4__
f4o = f4.o
else
val4 =
f4o =
endif

main: main.o $(f1o) $(f2o) $(f3o) $(f4o)
	g++ $^ -o main $(val1) $(val2) $(val3) $(val4)

f1.o: f1.cpp f1.h
	g++ -c f1.cpp -o f1.o $(val1)

f2.o: f2.cpp f2.h
	g++ -c f2.cpp -o f2.o $(val2)

f3.o: f3.cpp f3.h
	g++ -c f3.cpp -o f3.o $(val3)

f4.o: f4.cpp f4.h
	g++ -c f4.cpp -o f4.o $(val4)

main.o: main.cpp
	g++ -c $^ -o $@ $(val1) $(val2) $(val3) $(val4)

clean: 
	rm -f *.o -f main