#pragma once
#include <string> 


namespace NaiveServer
{
 struct Message
 {
	int m_client;
	std::string m_messageBody;
 };
}
