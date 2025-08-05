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
	std::vector<Client> _clients;

public:
	Channel();
	Channel(std::string &channel);
	~Channel();

	std::string getChannel() const;
	bool addClient(Client &client);
	void removeClient(Client &client);
	bool hasClient(Client &client);
	std::string getUserList() const;
};
