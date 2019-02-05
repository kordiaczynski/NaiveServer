#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/select.h>
#include <map>
#include <set>
#include <future>
#include <thread>
#include <chrono>
static const unsigned int uiPort = 8082;

std::set<int> clients;


#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <cassert>
#include "headers/clients.h"
#include "headers/outputqueue.h"
#include "headers/receiver.h" 
#include "headers/connection.h"
void setNonBlocking( int socket ){
	
	int flags;
	flags = fcntl(socket,F_GETFL,0);
	assert( flags != -1);
	fcntl(socket,F_SETFL, flags | O_NONBLOCK );
	
}

int main( int argn, char *argc[]){

	
	unsigned int port = 8082;
	if( argn > 1 )
	{
		sscanf( argc[1], "%u", &port );		
	}




	int serverfd = 0;
	int opt = 1;	
	int client = 0;
	
	sockaddr_in serverAddr;
	unsigned int sizeofAdress = sizeof( serverAddr );
	using namespace NaiveServer;

	Connection con( Connection::TCP );
	con.CreateAndListenOnPort( port );
	serverfd = con.GetFd();


	Clients cl;
	Receiver receiver;
		
	std::future<void> fut = std::async(std::launch::async, receiver , std::ref(cl));
	while( true )
	{
		sockaddr_in clientAddr;
		client = accept( serverfd, ( sockaddr*) &clientAddr, (socklen_t*)& sizeofAdress);
		cl.add(client);
					
	}
 return 0;
};

