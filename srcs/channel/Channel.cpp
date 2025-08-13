
#include "Channel.hpp"

//-----------------------------------------constructeur et destructeur--------------------------------

Channel::Channel() : _channel("channel"), _name_operator(""), _key_channel(""), _inviteOnly(false), _changeTopic(false), _passWord(false),
					 _limiteUsersInChannel(0), _limiteUserIsActive(false), _countUsersChannel(0) {}

Channel::Channel(std::string &channel) : _channel(channel), _name_operator(""), _key_channel(""), _inviteOnly(false), _changeTopic(false), _passWord(false),
										 _limiteUsersInChannel(0), _limiteUserIsActive(false), _countUsersChannel(0) {}
Channel::~Channel() {}

//----------------------------------------------Client----------------------------------------------------

void Channel::addClient(Client &client)
{
	if (hasClient(client) == false)
	{
		this->_clients.push_back(&client);
		client.sendReply(":server 332 " + client.getNickName() + " " + this->getChannel() + " " + ":Welcome is the channel !");
		_countUsersChannel++;
	}
}

void Channel::removeClient(Client &client)
{
	_clients.erase(std::find(_clients.begin(), _clients.end(), &client));
}

bool Channel::hasClient(Client &client)
{
	return (std::find(this->_clients.begin(), this->_clients.end(), &client) != this->_clients.end());
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
		std::cout << "inviter = " << *it << std::endl;
	}
	return false;
}

//-----------------------------------Allow changing the channel topic---------------------------------------------------------------

bool Channel::changeTopicOperator() const 
{ 
	return _changeTopic;
}

void Channel::setTopicOperator(bool value)
{ 
	_changeTopic = value;
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
