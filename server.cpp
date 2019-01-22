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
 
void setNonBlocking( int socket ){
	
	int flags;
	flags = fcntl(socket,F_GETFL,0);
	assert( flags != -1);
	fcntl(socket,F_SETFL, flags | O_NONBLOCK );
	
}

void Receiver( Clients & _rclients )
{

	fd_set read_flags, write_flags;
	struct timeval waitd = {10, 0};          // the max wait time for an event
    	int sel;       
	
	while(true)
	{
		int client = _rclients.getNext();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
 		if( client != 0 ){
			FD_ZERO(&read_flags);
       			FD_ZERO(&write_flags);
        		FD_SET(client, &read_flags);
        		FD_SET(client, &write_flags);

			sel = select( client+1, &read_flags, &write_flags, (fd_set*)0, &waitd );
			if( sel > 0 ){
				std::cout << "Sel is: " << sel << std::endl;
				if( FD_ISSET(client,&read_flags)){
			
					FD_CLR(client,&read_flags);
					std::cout << "Client " << client << " says: " << std::endl;			
					char in[255];
			 		memset(&in, 0, 255);

		         		recv(client, in, 255, 0);

					std::cout << std::endl;
					std::cout << in;
					std::cout << std::endl; 
				}
			}

	

		}


	}
};

//void sendMessages(

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

	Clients cl;
	
	std::future<void> fut = std::async(std::launch::async, Receiver , std::ref(cl));
	while( true )
	{
		sockaddr_in clientAddr;
		client = accept( serverfd, ( sockaddr*) &clientAddr, (socklen_t*)& sizeofAdress);
		cl.add(client);
					
	}
//	setNonBlocking(client);
	fd_set read_flags,write_flags; // the flag sets to be used
	struct timeval waitd = {10, 0};          // the max wait time for an event
    	int sel;       
	

	NaiveServer::OutputQueue outputQueue;	

	while(true){
 
	FD_ZERO(&read_flags);
        FD_ZERO(&write_flags);
        FD_SET(client, &read_flags);
        FD_SET(client, &write_flags);



	sel = select(client+1,&read_flags, &write_flags,(fd_set*)0,&waitd);

	if( sel > 0 ){
	
		if( FD_ISSET(client,&read_flags)){
			
	//		FD_CLR(client,&read_flags);
			
			char in[255];
			 memset(&in, 0, 255);

		         recv(client, in, 255, 0);

			std::cout << std::endl;
			std::cout << in;
			std::cout << std::endl; 
		}

/*		if( FD_ISSET(client,&write_flags)){
		
			FD_CLR(client,&write_flags);
			
			char buffor[] = "HTTP/1.1 404 Not Found";
			send(client, buffor,sizeof(buffor),0);	
		}
		
*/		
 		
	


		}
	}
//        FD_SET(STDIN_FILENO, &read_flags);
//        FD_SET(STDIN_FILENO, &write_flags);





/*	
//	std::async(std::launch::async, []()-> void { 

	int client = accept( serverfd, ( sockaddr*) &clientAddr, (socklen_t*)&sizeofAdress); 
	
	if( client > 0) {
	
		
	}


	});
*/
	return 0;
};

