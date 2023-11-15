.PHONY: clean

all: test_gmem test_smem
	
%: %.cu
	nvcc $^ -o $@ -O2 -code sm_60 -arch compute_60

clean:
	rm test_gmem test_smem

