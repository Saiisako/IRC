
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <vector>
#include <algorithm>
#include "Client.hpp"

class channel
{
private:
	std::string _channel;
	std::vector<client *> _clients;

public:
	channel(std::string &channel);
	~channel();

	std::string getChannel() const;
	bool addClient(client *client);
	void removeClient(client *client);
	bool hasClient(client *client);
	std::string getUserList() const;
};

#endif
