#include <mutex>
#include <condition_variable>
#include <set>

class Clients
{
public:
typedef std::set<int> ClientsContainer;

private:

std::mutex m_mutex;
std::condition_variable m_readyToRead;
std::condition_variable m_readyToWrite;

public:
ClientsContainer m_container;

void add(int client);
void remove(int client);
int  getNext();
};



