
#include "Channel.hpp"

//-----------------------------------------constructeur et destructeur--------------------------------

Channel::Channel() : _channel("channel"), _name_operator(""), _key_channel(""), _inviteOnly(false), _topic(false), _passWord(false),
					 _limiteUsersInChannel(0), _limiteUserIsActive(false), _countUsersChannel(0), _nameTopic("") {}

Channel::Channel(std::string &channel) : _channel(channel), _name_operator(""), _key_channel(""), _inviteOnly(false), _topic(false), _passWord(false),
										 _limiteUsersInChannel(0), _limiteUserIsActive(false), _countUsersChannel(0), _nameTopic("") {}
Channel::~Channel()
{
	_clients.clear();
}

//----------------------------------------------Client----------------------------------------------------

void Channel::addClient(Client &client)
{
	if (hasClient(client) == false)
	{
		this->_clients.push_back(&client);

		//:jelecoq!~jelecoq@62.129.BF859D.D76970 JOIN :#42
		client.sendReply(':' + client.getNickName() + '!' + client.getUserName() + '@' + client.getHostName() + " JOIN :" + _channel);
		if (_nameTopic != "")
			client.sendReply(":server 332 " + client.getNickName() + ' ' +  _channel + " :" + _nameTopic);
		else
			client.sendReply(":server 331 " + client.getNickName() + ' ' + _channel + " :No topic is set");
		//:server 332 <nick> #canal :<topic du canal>
		//:server 331 <nick> #canal :No topic is set
		//:server 353 <nick> = #canal :@admin1 +modo1 user2 user3
		_countUsersChannel++;
	}
}

bool Channel::isInChannel(const std::string& nick) const 
{
	for (size_t i = 0; i < _clients.size(); ++i)
	{
		if (_clients[i]->getNickName() == nick)
			return true;
	}
	return false;
}

void Channel::removeClient(Client &client)
{
	_clients.erase(std::find(_clients.begin(), _clients.end(), &client));
}

bool Channel::hasClient(Client &client)
{
	for (std::vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (*it && (*it)->getNickName() == client.getNickName())
			return true;
	}
	return false;
}

std::string Channel::getChannel() const { return _channel; }

//-------------------------------------------Operator------------------------------------------------------

void Channel::addOperator(const std::string &nickname)
{
	_operators.insert(nickname);
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

int Channel::removeOperator(const std::string &name)
{
	size_t erased = _operators.erase(name);
	return erased > 0;
}

//---------------------list all users in the channel : operator and others---------------------------------

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

std::vector<Client *> &Channel::getUserListV(void) { return (_clients); }

//----------------------------------Message all users in the channel except the user himself---------------------

void Channel::broadcast(const std::string &msg, Client &client)
{
	for (unsigned int i = 0; i < this->_clients.size(); i++)
	{
		if (_clients[i]->getNickName() == client.getNickName())
			continue;
		_clients[i]->sendReply(msg);
	}
}

//---------------------------------------Invitation to the channel --------------------------------------------------------

bool Channel::inviteOnlyIsActive() const
{
	return _inviteOnly;
}

void Channel::setInviteOnly(bool value)
{
	_inviteOnly = value;
}

void Channel::addInvite(const std::string &name_invite)
{
	_inviteUserInChannel.insert(name_invite);
}

bool Channel::userIsListeInvite(const std::string &name)
{
	for (std::set<std::string>::const_iterator it = _inviteUserInChannel.begin(); it != _inviteUserInChannel.end(); ++it)
	{
		if (*it == name)
			return true;
		std::cout << *it << std::endl;
	}
	return false;
}

bool Channel::isInvited(const std::string &nick) const 
{
	for (std::set<std::string>::const_iterator it = _inviteUserInChannel.begin(); it != _inviteUserInChannel.end(); ++it)
	{
		if (*it == nick)
			return true;
	}
	return false;
}

//-----------------------------------Allow changing the channel topic---------------------------------------------------------------

bool Channel::TopicOperatorIsActive() const
{
	return _topic;
}

void Channel::setTopicOperator(bool value)
{
	_topic = value;
}

std::string Channel::getNameTopic() const
{
	return _nameTopic;
}

void Channel::setNameTopic(const std::string &topic)
{
	_nameTopic = topic;
}

//----------------------------------------Key channel----------------------------------------------------------------------------

std::string Channel::getKey() const
{
	return _key_channel;
}

void Channel::setKey(const std::string &key)
{
	_key_channel = key;
}

void Channel::setPassWord(bool value)
{
	_passWord = value;
}

bool Channel::isPassorWord() const
{
	return _passWord;
}

//-------------------------------Limite users in the channel-------------------------------------------------------------------------

void Channel::setLimiteUserIsActive(bool value)
{
	_limiteUserIsActive = value;
}

bool Channel::isLimiteUserIsActive() const
{
	return _limiteUserIsActive;
}

int Channel::getLimiteUserChannel() const
{
	return _limiteUsersInChannel;
}

void Channel::setLimiteUserChannel(const int limite)
{
	_limiteUsersInChannel = limite;
}

int Channel::getCountUserChannel() const
{
	return _countUsersChannel;
}
void Channel::addCountUserChannel()
{
	_countUsersChannel += 1;
}
