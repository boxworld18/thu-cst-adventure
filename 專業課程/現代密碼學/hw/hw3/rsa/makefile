.PHONY: build test

build: rsa.cpp test
	g++ rsa.cpp -o rsa -O2 -lgmp -lgmpxx

test: test_gen.py
	python3 test_gen.py

clean:
	rm -rf rsa testcases/