.PHONY: clean

all: main_0 main_1 main_2 main_3 main_fast

main_0: main.cpp
	icc $^ -o $@ -O0

main_1: main.cpp
	icc $^ -o $@ -O1

main_2: main.cpp
	icc $^ -o $@ -O2

main_3: main.cpp
	icc $^ -o $@ -O3

main_fast: main.cpp
	icc $^ -o $@ -fast

clean:
	rm main_*
