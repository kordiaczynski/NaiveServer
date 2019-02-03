
#include "headers/receiver.h"
#include "headers/outputqueue.h"
#include "headers/clients.h"
#include <future>
#include <cstring>

#include <chrono>



namespace std {

	namespace chrono {

	timeval timevalFromDuration( const std::chrono::duration<int,std::milli> & ms )
	{
	
		unsigned int second = ms.count()/ 1000;
		unsigned int miliseconds = ms.count() - second * 1000;
		int microseconds = miliseconds * 1000;
		
		return { second, microseconds };
	}
	}

}



namespace NaiveServer
{

void Receiver::operator()( Clients & _rclients ){

	NaiveServer::OutputQueue output;
	fd_set read_flags, write_flags;
	struct timeval waitd = std::chrono::timevalFromDuration( std::chrono::duration<int,std::milli>(500));	
	std::future<void> fut = std::async(std::launch::async, std::ref(output));
	while(true)
	{
		int client = _rclients.getNext();
 		if( client != 0 ){
	
			FD_ZERO(&read_flags);
        		FD_SET(client, &read_flags);
	
			int selectResult = select( client+1, &read_flags, NULL, NULL, &waitd );
			if( selectResult > 0 ){
				if( FD_ISSET(client,&read_flags)){
			
					std::cout << "Client " << client << " says: " << std::endl;			
					char in[2049];
			 		memset(&in, 0, sizeof(in));

		         		recv(client, in, sizeof(in), 0);
					output.AddMessage( NaiveServer::Message( client, m_fixedMessage ));
					std::cout << std::endl;
					std::cout << in;
					std::cout << std::endl; 
				}
			}

	

		}


	}
}
}
