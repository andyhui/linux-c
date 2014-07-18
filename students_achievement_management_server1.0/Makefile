CC=gcc
CXX=g++
#CFLAGS= -I /usr/include/mysql/ -Wall -g #DDbug
CPPFLAGS= -I/usr/include/mysql/ -I/usr/local/include/jwsmtp-1.32 -g #DDbug
#CPPFLAGS= -I/usr/include/mysql/ -I./jwsmtp-1.32.15 -g #DDbug
OBJS=
LIBS=-lmysqlclient /usr/local/lib/libjwsmtp.a
#LIBS=-lmysqlclient `pkg-config --libs --cflags jwsmtp-<version>`

all:server

server: main.o administrator.o teacher.o student.o RegAndLog.o
	$(CXX) -o $@ $^ $(CPPFLAGS) $(LIBS)

clean:
	rm -f core *.o server

wc:
	wc *.[ch]
