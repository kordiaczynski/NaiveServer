#pragma once

#include <queue>
#include <mutex>
#include <memory>

template <typename T>
class MessageQueue 
{
	protected:

	std::queue<T> m_messages;

	virtual bool addMessage(const T& _mesasage ) = 0;

	public:
	
	std::mutex  mut;

	std::condition_variable cv;	
	bool AddMessage(T _message)
	{
		return addMessage(_message);
	}
	
	
};

