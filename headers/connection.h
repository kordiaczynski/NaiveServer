#pragma once


namespace NaiveServer {
	class Connection
	{
		private:
		int serverFd;
		void getFamilyAndType( int & family, int & type);
		
		public:
		enum Type { UDP,TCP} m_type;
		enum Error { ErNone,ErCreateSocket, ErBindSocket,ErListen } m_error;
		Connection( const Type type) : m_type( type), serverFd(0), m_error( ErNone )  {};
		bool BindOnPort( unsigned int port );		
		bool CreateAndListenOnPort( unsigned int port );
		int  GetFd() const;
	};
}
