/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:03:45 by skock             #+#    #+#             */
/*   Updated: 2025/08/11 15:03:48 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() {}
Channel::Channel(std::string &channel) : _channel(channel), _name_operator("") {}
Channel::~Channel() {}
std::string Channel::getChannel() const { return _channel; }

bool Channel::addClient(Client &client)
{
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
	for (unsigned int i = 0; i < this->_clients.size(); i++)
	{
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

void Channel::broadcast(const std::string &msg, Client &client)
{
	for (unsigned int i = 0; i < this->_clients.size(); i++)
	{
		if (_clients[i]->getNickName() == client.getNickName())
			continue;
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

void Channel::setOperator(const std::string &name)
{
	_name_operator = name;
}
std::string Channel::getOperator() const
{
	return _name_operator;
}
