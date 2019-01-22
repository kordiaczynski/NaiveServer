#include <queue>
#include "messagequeue.h"
#include "message.h"

namespace NaiveServer
{
	class OutputQueue: public MessageQueue<Message>
	{
		bool addMessage( const Message& message )
		{
			std::shared_ptr<std::mutex> ptr = m_mutex.lock();;
			std::lock_guard<std::mutex> lock(*ptr);		
			return true;
		}		
	};
}
