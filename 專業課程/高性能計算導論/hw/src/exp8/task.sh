srun -n 8 vtune -collect hotspots -trace-mpi -result-dir task1 -- ./main 2020010869
srun -n 8 vtune -collect uarch-exploration -trace-mpi -result-dir task2 -- ./main 2020010869
