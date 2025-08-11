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
	std::string _key;
	std::vector<Client *> _clients;
	std::set<std::string> _operators;
	std::set<std::string> _inviteUserInChannel;
	bool _inviteOnly;
	bool _changeTopic;
	bool _passWord;
	bool _limiteUser;

public:
	Channel();
	Channel(std::string &channel);
	~Channel();

	std::string getChannel() const;

	bool addClient(Client &client);
	void addOperator(const std::string &nickname);
	void removeClient(Client &client);
	bool hasClient(Client &client);
	std::string getUserList();
	void broadcast(const std::string &msg, Client &client);

	std::string getOperator() const;
	void setOperator(const std::string &name);
	bool isOperator(const std::string &name) const;
	int removeOperator(const std::string &name);

	bool isInviteOnly() const;
	void setInviteOnly(bool value);
	void addInvite(const std::string &name_invite);
	bool userIsListeInvite(const std::string &name);

	bool changeTopicOperator() const;
	void setTopicOperator(bool value);

	std::string getKey() const;
	void setKey(const std::string &key);

	void setPassWord(bool value);
	bool isPassorWord() const;

	void setLimiteUser(bool value);
	bool isLimiteUser() const;
};
