CXXFLAGS  =-std=c++11 $(shell pkg-config --cflags libndn-cxx)
LDFLAGS =-std=c++11 $(shell pkg-config --libs libndn-cxx)
CC = $(CXX)

app: reg

reg: reg.o

clean:
	rm -Rf reg *.o
