CC=gcc
CXX=g++
#CFLAGS= -I /usr/include/mysql/ -Wall -g #DDbug
CPPFLAGS= -I /usr/include/mysql/ -g #DDbug
OBJS=
LIBS=-lmysqlclient

all:server

server: main.o administrator.o teacher.o
	$(CXX) -o $@ $^ $(CPPFLAGS) $(LIBS)

clean:
	rm -f core *.o server

wc:
	wc *.[ch]
