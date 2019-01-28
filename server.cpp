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
#include "clients.h"
#include "outputqueue.h"
#include "receiver.h" 
void setNonBlocking( int socket ){
	
	int flags;
	flags = fcntl(socket,F_GETFL,0);
	assert( flags != -1);
	fcntl(socket,F_SETFL, flags | O_NONBLOCK );
	
}

int main(){

	int serverfd = 0;
	int opt = 1;
	
	sockaddr_in serverAddr;
	unsigned int sizeofAdress = sizeof( serverAddr );

	if(( serverfd = socket( AF_INET, SOCK_STREAM, 0 )) == 0) {
		std::cout << "Unable to create socket";	
		return -1;
	}

	
	
	if( setsockopt( serverfd, SOL_SOCKET, SO_REUSEADDR, &opt,sizeof(opt)) != 0 ){
		std::cout << "Unable to set options" << errno;
		return -1;
	}
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons( uiPort );
	
	
	if( bind( serverfd,(sockaddr*) &serverAddr, sizeofAdress ) )
	{
		std::cout << "Unable to bind";
		return -1;
	}


	if( listen( serverfd, 3) )
	{
		std::cout << "Listen";
		return -1;
	}

	int client = 0;	

	using namespace NaiveServer;

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

