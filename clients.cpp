#include "headers/clients.h"
void Clients::add(int _client)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_container.insert( _client );
}

void Clients::remove(int _client)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_container.erase(_client);
}


int Clients::getNext()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	static ClientsContainer::iterator it = m_container.begin();
	int result = 0 ;
	if( it != m_container.end()){
		result = *it++;
	}
	else
	{
		it = m_container.begin();
	}
	return result;
}
