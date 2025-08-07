
#include "Channel.hpp"

Channel::Channel() {}
Channel::Channel(std::string &channel) : _channel(channel) {}
Channel::~Channel() {}
std::string Channel::getChannel() const { return _channel; }

bool Channel::addClient(Client &client)
{
	// std::string nick = client.getNickName();
	// if (_clients.count(nick))
	//	return false;
	// else

	if (hasClient(client) == false)
	{
		this->_clients.push_back(&client);
		client.sendReply(":server 332 " + client.getNickName() + " " + this->getChannel() + " " + ":Bienvenue dans le canal !");
		return (true);
	}
	return false;
}

void Channel::removeClient(Client &client)
{
	(void)client;
	_clients.erase(std::find(_clients.begin(), _clients.end(), &client));
}

std::string Channel::getUserList()
{
	std::string list_clients;
	// std::cout << "First client = " << &(*_clients.begin())->getNickName() << std::endl;
	//  for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	//{
	//	std::cout << (*it)->getNickName() << std::endl;
	//  }

	for (unsigned int i = 0; i < this->_clients.size(); i++)
	{
		std::cout << "NICKNAME[" << i << "] = [" << _clients[i]->getNickName() << "]" << std::endl;
		if (i > 0)
			list_clients += " ";
		if (isOperator(_clients[i]->getNickName()) && _operators.count(_clients[i]->getNickName()))
			list_clients += "@" + _clients[i]->getNickName();
		else
			list_clients += this->_clients[i]->getNickName();
	}
	return (list_clients);
}

bool Channel::hasClient(Client &client)
{
	return (std::find(this->_clients.begin(), this->_clients.end(), &client) != this->_clients.end());
}
void Channel::addOperator(const std::string &nickname)
{
	_operators.insert(nickname);
}

void Channel::broadcast(const std::string &msg)
{
	for (unsigned int i = 0; i < this->_clients.size(); i++)
	{
		_clients[i]->sendReply(msg);
	}
}

bool Channel::isOperator(const std::string &name) const
{
	for (std::set<std::string>::iterator it = _operators.begin(); it != _operators.end(); ++it)
	{
		if (*it == name)
			return true;
	}
	return false;
}

// Client *Channel::getClientByName(const std::string &nickname) const
//{
//	std::map<std::string, Client *>::const_iterator it = _clientMap.find(nickname);
//	if (it != _clientMap.end())
//		return it->second;
//	return NULL;
// }
