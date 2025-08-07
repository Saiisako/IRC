#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "Client.hpp"

class Channel
{
private:
	std::string _channel;
	std::vector<Client *> _clients;
	std::set<std::string> _operators;
	// std::map<std::string, Client *> _clientMap;

public:
	Channel();
	Channel(std::string &channel);
	~Channel();

	std::string getChannel() const;
	Client *getClassClient() const;
	bool addClient(Client &client);
	void addOperator(const std::string &nickname);
	void removeClient(Client &client);
	bool hasClient(Client &client);
	std::string getUserList();
	void broadcast(const std::string &msg);
	bool isOperator(const std::string &name) const;
	Client *getClientByName(const std::string &nickname) const;
};
