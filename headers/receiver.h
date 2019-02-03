#pragma once
#include "clients.h"

namespace NaiveServer
{

       	      
	class Receiver 
	{
		private:
 const  char * m_fixedMessage = 
"HTTP/1.1 200 OK\n"
"Date: Sat, 26 Jan 2019 21:58:30 GMT\n"
"Content-Type: application/json; charset=utf-8\n"
"Content-Length: 55\n"
"Connection: keep-alive\n"
"Set-Cookie: __cfduid=dc47689ee73dda142ebba32a00f72ff7b1548528870; expires=Sun, 26-Jan-20 18:54:30 GMT; path=/; domain=.typicode.com; HttpOnly\n"
"X-Powered-By: Express\n"
"Vary: Origin, Accept-Encoding\n"
"Access-Control-Allow-Credentials: true\n"
"Cache-Control: public, max-age=14400\n"
"Pragma: no-cache\n"
"Expires: Sat, 26 Jan 2019 22:54:30 GMT\n"
"X-Content-Type-Options: nosniff\n"
"Etag: W/\"124-yiKdLzqO5gfBrJFrcdJ8Yq0LGnU\"\n"
"Via: 1.1 vegur\n"
"CF-Cache-Status: HIT\n"
"Accept-Ranges: bytes\n"
"Server: cloudflare\n"
"CF-RAY: 49f5303da18e5960-VIE\n"
"\n{"
"\"userId\": 1,"
"\"id\": 1,"
"\"title\": \"TYTUL\","
"\"body\": \"CIALO\""
"}\n";
		
	


	public:
			void operator()( Clients & _rclients );
	};
}
