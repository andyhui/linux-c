CC=gcc
C++=g++
CFLAGS=-I../include -g #-DDEBUG
OBJS=
LIBS=

all: tcpclient tcpserver udpclient udpserver

tcpclient: TCPEchoClient.o DieWithError.o
	${CC} -o $@ $^

tcpserver: TCPEchoServer-ForkN.o CreateTCPServerSocket.o AcceptTCPConnection.o HandleTCPClient.o DieWithError.o
#tcpserver: TCPEchoServer.o HandleTCPClient.o DieWithError.o
	${CC} -o $@ $^ -lpthread

udpclient: UDPEchoClient-Timeout.o DieWithError.o
	${CC} -o $@ $^

udpserver: UDPEchoServer.o DieWithError.o
	${CC} -o $@ $^

clean:
	rm -f core *.o tcpclient tcpserver udpclient udpserver

wc:
	wc *.[ch]
