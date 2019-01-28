#include <queue>
#include "messagequeue.h"
#include "message.h"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
namespace NaiveServer
{
	class OutputQueue: public MessageQueue<Message>
	{

		bool addMessage( const Message& message )
		{
			std::unique_lock<std::mutex> lock( mut );								
			m_messages.push(message);
			cv.notify_all();
			return true;
		}		
	public:

		void operator()()
		{

////*
			while(true)
			{
			std::unique_lock<std::mutex> lock( mut );
			while( m_messages.size() == 0)
			{
				cv.wait(lock);
			}
				
			const Message& message = m_messages.front();
			send( message.m_client, message.m_messageBody.c_str(), message.m_messageBody.size(),0 );
			m_messages.pop();
			

			}///*/	
		}





	};
}
