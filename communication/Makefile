CC=gcc
C++=g++
CFLAGS=-I ../include -g #DDEBUG
OBJS=
LIBS=

all:tcpclient tcpserver

tcpclient: msg_conn.o
	$(CC) -o $@ $^

tcpserver: msg_server.o HandleTCPClient2.o HandleUDPClient.o
	$(CC) -o $@ $^

clean:
	rm -f core *.o tcpclient tcpserver

wc:
	wc *.[ch]
