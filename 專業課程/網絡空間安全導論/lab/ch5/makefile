.PHONY: build test

build: paillier.cpp test
	g++ paillier.cpp -o paillier -O2 -lgmp -lgmpxx

test: test_gen.py
	python3 test_gen.py

clean:
	rm -rf paillier testcases/