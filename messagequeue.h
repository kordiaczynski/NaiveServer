#include <queue>
#include <mutex>
#include <memory>

template <typename T>
class MessageQueue 
{
	protected:
	std::weak_ptr<std::mutex> m_mutex;
	std::queue<T> m_messages;
	
	virtual bool addMessage(const T& _mesasage ) = 0;

	public:
	
	bool AddMessage(T _message)
	{
		return addMessage(_message);
	}
	
	
};

