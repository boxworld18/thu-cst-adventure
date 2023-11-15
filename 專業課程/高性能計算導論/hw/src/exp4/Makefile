.PHONY: clean
	
run_cuda: main.cu
	nvcc main.cu -o run_cuda -O2 -code sm_60 -arch compute_60

clean:
	rm run_cuda
