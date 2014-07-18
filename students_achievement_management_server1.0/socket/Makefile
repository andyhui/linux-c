CC=gcc
C++=g++
CFLAGS=-I../include -g #-DDEBUG
OBJS=
LIBS=

all: client server 

client: Client.o DieWithError.o
	${CC} -o $@ $^

server: Server.o CreateTCPServerSocket.o AcceptTCPConnection.o HandleTCPClient.o DieWithError.o
	${CC} -o $@ $^ -lpthread

clean:
	rm -f core *.o client server

wc:
	wc *.[ch]
