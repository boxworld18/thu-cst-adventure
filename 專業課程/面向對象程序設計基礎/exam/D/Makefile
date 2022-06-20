CC := g++
override CFLAGS += -std=c++14
TARGET := main

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all:
	@make main CFLAGS="-DSUBTASK1 -DSUBTASK2 -DSUBTASK3 -DSUBTASK4"
subtask1:
	@make main CFLAGS="-DSUBTASK1"
subtask2:
	@make main CFLAGS="-DSUBTASK1 -DSUBTASK2"
subtask3:
	@make main CFLAGS="-DSUBTASK1 -DSUBTASK2 -DSUBTASK3"
subtask4:
	@make main CFLAGS="-DSUBTASK1 -DSUBTASK2 -DSUBTASK3 -DSUBTASK4"

$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o

.PHONY: all clean subtask1 subtask2 subtask3 subtask4