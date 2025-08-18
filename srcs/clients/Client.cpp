
#include "Client.hpp"
#include "Error.hpp"

//------------------------------constructeur - destructeur---------------------------------

Client::Client(int fd) : _fd(fd), _nickname(""), _username(""), _realname(""), _hostname(""),
						 _registredNick(false), _registredUser(false), _registredPassWord(false), _welcomeSent(false) {}
Client::~Client() {}

//-------------------------------config registred client---------------------------------

int Client::getFd() const
{
	return this->_fd;
}

std::string Client::getNickName() const
{
	return this->_nickname;
}

std::string Client::getUserName() const
{
	return _username;
}

std::string Client::getRealName() const
{
	return _realname;
}

std::string Client::getHostName() const
{
	return _hostname;
}

void Client::setNickname(const std::string &nick, std::vector<Client *> clients, Client &client)
{
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		if (clients[i]->getNickName() == nick)
		{
			std::cout << "CLIENT NICK " << clients[i]->getNickName() << std::endl;
			client.sendReply(ERR_NICKNAMEINUSE(client.getNickName()));
			return;
		}
	}
	this->_nickname = nick;
}

void Client::setUserName(const std::string &user)
{
	_username = user;
}

void Client::setRealName(const std::string &realname)
{
	_realname = realname;
}

void Client::setHostNAme(const std::string &hostname)
{
	_hostname = hostname;
}

//-----------------------------registries----------------------------------------------

bool Client::getRegistredUser() const
{
	return _registredUser;
}

bool Client::getRegistredNick() const
{
	return _registredNick;
}

bool Client::getRegistredPassWord() const
{
	return _registredPassWord;
}

void Client::setRegistredUser(bool arg)
{
	_registredUser = arg;
}

void Client::setRegistredNick()
{
	_registredNick = true;
}

void Client::setRegistredPassWord()
{
	_registredPassWord = true;
}

bool Client::isReadyToRegister() const
{
	if (_registredNick == true && _registredUser == true && _registredPassWord == true)
		return true;
	return false;
}

//--------------------------------message_client-------------------------------------------

void Client::sendReply(const std::string &msg) const
{
	std::string fullMsg = msg + "\r\n";
	ssize_t bytes = write(_fd, fullMsg.c_str(), fullMsg.size());

	if (bytes == -1)
		std::cerr << "Erreur lors de l'envoi à fd " << _fd << " : " << strerror(errno) << std::endl;
}

bool Client::isWelcomeSent() const
{
	return _welcomeSent;
}

void Client::setWelcomeSent(bool b)
{
	_welcomeSent = b;
}

//----------------------------------Debug serveur-----------------------------------------------------

std::ostream &operator<<(std::ostream &flux, const Client &c)
{
	flux << "client Fd = " << c.getFd() << std::endl;
	flux << "Nickname = " << c.getNickName() << std::endl;
	flux << "Realname = " << c.getRealName() << std::endl;
	flux << "Username = " << c.getUserName() << std::endl;
	flux << "is nickname registered = " << c.getRegistredNick() << std::endl;
	flux << "is password registered = " << c.getRegistredPassWord() << std::endl;
	flux << "is user registered = " << c.getRegistredUser() << std::endl;
	return (flux);
}
