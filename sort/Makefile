target=sortApp
CC=g++
CFLAGS=-c
put=-o
cppFileSuffix=.cpp
oFileSuffix=.o
src=$(wildcard ./*.cpp)
ofile=$(patsubst ./%.cpp, ./%.o, $(src))

$(target):$(ofile)
	$(CC) $^ $(put) $@

%$(oFileSuffix):%$(cppFileSuffix)
	$(CC) $(CFLAGS) $< $(put) $@

.PHONY:clean
clean:
	rm$(ofile) $(target) -f
