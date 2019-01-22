CC=g++

ServerApp: server.cpp clients.cpp  
	$(CC) -o ServerApp clients.cpp server.cpp -std=c++11 
