.PHONY: clean

all: aplusb

aplusb-baseline.o: aplusb-baseline.cpp aplusb.h
	icpc aplusb-baseline.cpp -c -o aplusb-baseline.o -g

aplusb-autosimd.o: aplusb-autosimd.cpp aplusb.h
	icpc aplusb-autosimd.cpp -c -o aplusb-autosimd.o -g -xhost

aplusb-intrinsic.o: aplusb-intrinsic.cpp aplusb.h
	icpc aplusb-intrinsic.cpp -c -o aplusb-intrinsic.o -g -xhost

aplusb: aplusb.cpp aplusb-baseline.o aplusb-autosimd.o aplusb-intrinsic.o aplusb.h
	icpc -std=c++17 aplusb.cpp aplusb-baseline.o aplusb-autosimd.o aplusb-intrinsic.o -o aplusb -g -xhost

clean:
	rm -f *.o aplusb
