#include "headers/connection.h"


#include <netinet/in.h>
#include  <sys/select.h>


namespace NaiveServer {

void Connection::getFamilyAndType( int & family, int & type ) {
	switch( m_type )
	{
		case TCP:
			family = AF_INET;
			type   = SOCK_STREAM;
			break;
		case UDP:
			family = AF_INET;
			type   = SOCK_DGRAM;
			break;
	}
}

bool Connection::BindOnPort( unsigned int port ){
	sockaddr_in serverAddr;
	size_t addrSize = sizeof( serverAddr );
			
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr  = INADDR_ANY;
	serverAddr.sin_port   = htons( port );

	if( bind( serverFd, (sockaddr*) &serverAddr, addrSize ) != 0 )
	{
		return false;
	}
					
	return true;
}

bool Connection::CreateAndListenOnPort( unsigned int port ){
	int family = AF_INET;
	int type           = SOCK_STREAM;
	getFamilyAndType( family, type );
	serverFd = socket(family, type,0);
	if( serverFd == 0 ){
		m_error = ErCreateSocket;						
	}
	if( m_error == ErNone ){
		if( BindOnPort( port ) == false ){
			m_error = ErBindSocket;
		}
	}
	if( m_error == ErNone ){
		if( listen( serverFd, 3) ){
			m_error = ErListen;
		}
	}			
			

	if( m_error == ErNone){
		return true;
	} else {
		return false;
	}
}	

int Connection::GetFd() const 
{
	return serverFd;
}


}

			
