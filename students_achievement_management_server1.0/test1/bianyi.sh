g++    -c -o Client.o Client.cpp
g++    -c -o DieWithError.o DieWithError.cpp
g++ -o Client Client.o DieWithError.o -g
g++    -c -o CreateTCPServerSocket.o CreateTCPServerSocket.cpp
g++    -c -o AcceptTCPConnection.o AcceptTCPConnection.cpp
g++    -c -o administrator.o administrator.cpp -lmysqlclient
g++    -c -o student.o student.cpp -lmysqlclient
g++    -c -o teacher.o teacher.cpp -lmysqlclient
g++    -c -o RegAndLog.o RegAndLog.cpp -lmysqlclient
g++    -c -o HandleTCPClient.o HandleTCPClient.cpp -lmysqlclient
g++    -c -o Server.o Server.cpp -lmysqlclient

g++ -o Server CreateTCPServerSocket.o AcceptTCPConnection.o DieWithError.o administrator.o student.o teacher.o RegAndLog.o HandleTCPClient.o Server.o -lmysqlclient -g

