CXXFLAGS := -O3 -std=c++11

.PHONY: clean

all: mpi_sync mpi_async

mpi_sync: mpi_sync.cpp
	mpicxx $^ ${CXXFLAGS} -o $@

mpi_async: mpi_async.cpp
	mpicxx $^ ${CXXFLAGS} -o $@

clean:
	rm mpi_sync mpi_async
