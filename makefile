CC=g++

ServerApp: server.cpp clients.cpp  
	$(CC) -o ServerApp clients.cpp server.cpp receiver.cpp -std=c++11 -g 
