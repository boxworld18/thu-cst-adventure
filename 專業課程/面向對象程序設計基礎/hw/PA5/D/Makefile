export INCLUDE_PATH
CXXFLAGS = -I$(INCLUDE_PATH) -O2 -std=c++11

all: main

% : %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@