CC=gcc
CXX=g++
CFLAGS=-I ../include -g #DDEBUG
OBJS=
LIBS=

all:server

server: main.o administrator.o
	$(CXX) -o $@ $^ $(CFLAGS)

clean:
	rm -f core *.o server

wc:
	wc *.[ch]
