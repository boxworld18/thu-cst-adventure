.PHONY: build test

build: sha3.cpp test
	g++ sha3.cpp -o sha3 -O2 

test: test_gen.py
	python3 test_gen.py

clean:
	rm -rf sha3 testcases/