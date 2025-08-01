
#include "Channel.hpp"

channel::channel(std::string &channel) : _channel(channel) {}
channel::~channel() {}
std::string channel::getChannel() const { return _channel; }

bool channel::addClient(client *client)
{
	if (hasClient(client) == false)
	{
		this->_clients.push_back(client);
		return (true);
	}
	return false;
}
void channel::removeClient(client *client)
{
	this->_clients.erase(std::remove(this->_clients.begin(), this->_clients.end(), client), this->_clients.end());
}
std::string channel::getUserList() const
{
	std::string list_clients;

	for (unsigned int i; i < this->_clients.size(); i++)
	{
		if (i > 0)
			list_clients += " ";
		list_clients += this->_clients[i]->getNickName();
	}
	return (list_clients);
}

bool channel::hasClient(client *client)
{
	return (std::find(this->_clients.begin(), this->_clients.end(), client) != this->_clients.end());
}
