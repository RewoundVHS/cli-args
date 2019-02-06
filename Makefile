CXXFLAGS = -g -O3 -Wall -Wextra -Wuninitialized -pedantic -Wshadow -Weffc++ -std=c++14

OBJS = counter

all: ${OBJS}

clean:
	rm -f counter *.o
