#pragma once
#include <string> 


namespace NaiveServer
{
 struct Message
 {
	int m_client;
	std::string m_messageBody;

	Message( int _client, std::string _message):
	m_client(_client), m_messageBody(_message)
	{
	}
 };
}
