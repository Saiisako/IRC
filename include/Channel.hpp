#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include "Client.hpp"
#include <set>

class Channel
{
	private:
		std::string _channel;
		std::string _name_operator;
		std::vector<Client *> _clients;
		std::set<std::string> _operators;

	public:
		Channel();
		Channel(std::string &channel);
		~Channel();

		std::string getChannel() const;
		std::string getOperator() const;
		bool addClient(Client &client);
		void addOperator(const std::string &nickname);
		void removeClient(Client &client);
		bool hasClient(Client &client);
		std::string getUserList();
		void broadcast(const std::string &msg, Client &client);
		void setOperator(const std::string &name);
		bool isOperator(const std::string &name) const;
};
