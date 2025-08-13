#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include "Client.hpp"

class Channel
{
private:
	std::string _channel;
	std::string _name_operator;
	std::string _key_channel;
	std::vector<Client *> _clients;
	std::set<std::string> _operators;
	std::set<std::string> _inviteUserInChannel;
	bool _inviteOnly;
	bool _topic;
	bool _passWord;
	int _limiteUsersInChannel;
	bool _limiteUserIsActive;
	int _countUsersChannel;
	std::string _nameTopic;

public:
	Channel();
	Channel(std::string &channel);
	~Channel();

	std::string getChannel() const;

	void addClient(Client &client);
	void addOperator(const std::string &nickname);
	void removeClient(Client &client);
	bool hasClient(Client &client);
	std::string getUserList();
	void broadcast(const std::string &msg, Client &client);

	std::string getOperator() const;
	void setOperator(const std::string &name);
	bool isOperator(const std::string &name) const;
	int removeOperator(const std::string &name);

	bool inviteOnlyIsActive() const;
	void setInviteOnly(bool value);
	void addInvite(const std::string &name_invite);
	bool userIsListeInvite(const std::string &name);

	bool TopicOperatorIsActive() const;
	void setTopicOperator(bool value);

	std::string getKey() const;
	void setKey(const std::string &key);

	void setPassWord(bool value);
	bool isPassorWord() const;

	void setLimiteUserIsActive(bool value);
	bool isLimiteUserIsActive() const;

	int getLimiteUserChannel() const;
	void setLimiteUserChannel(const int limite);

	int getCountUserChannel() const;
	void addCountUserChannel();

	std::string getNameTopic() const;
	void setNameTopic(const std::string &topic);
};
