.PHONY: build test

build: aes.cpp test
	g++ aes.cpp -o aes -O2 

test: test_gen.py
	python3 test_gen.py

clean:
	rm -rf aes testcases/