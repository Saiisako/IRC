
#include "Channel.hpp"

Channel::Channel(std::string &channel) : _channel(channel) {}
Channel::~Channel() {}
std::string Channel::getChannel() const { return _channel; }

bool Channel::addClient(Client &client)
{
	if (hasClient(client) == false)
	{
		this->_clients.push_back(client);
		return (true);
	}
	return false;
}

void Channel::removeClient(Client &client)
{
	(void)client;
	// _clients.erase(std::find(_clients.begin(), _clients.end(), client));
}

std::string Channel::getUserList() const
{
	std::string list_clients;

	for (unsigned int i = 0; i < this->_clients.size(); i++)
	{
		if (i > 0)
			list_clients += " ";
		list_clients += this->_clients[i].getNickName();
	}
	return (list_clients);
}

bool Channel::hasClient(Client &client)
{
	return (std::find(this->_clients.begin(), this->_clients.end(), client) != this->_clients.end());
}
