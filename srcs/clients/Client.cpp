
#include "Client.hpp"

client::client(int fd) : _fd(fd), _nickname(""), _username(""), _realname(""),
						 _registredNick(false), _registredUser(false), _registredPassWord(false) {}
client::~client() {}

int client::getFd() const { return this->_fd; }
std::string client::getNickName() const { return this->_nickname; }
std::string client::getUserName() const { return _username; }
std::string client::getRealName() const { return _realname; }
bool client::getRegistredUser() const { return _registredUser; }
bool client::getRegistredPassWord() const {return _registredPassWord;}
bool client::getRegistredNick() const { return _registredNick; }

void client::setNickname(const std::string &nick) { this->_nickname = nick; }
void client::setUserName(const std::string &user) { _username = user; }
void client::setRealName(const std::string &realname) { _realname = realname; }
void client::setRegistredUser() { _registredUser = true;}
void client::setRegistredNick() { _registredNick = true;}
void client::setRegistredPassWord() {_registredPassWord = true;}

bool client::isReadyToRegister() const
{
	if (_registredNick == true && _registredUser == true)
		return true;
	return false;
}

void client::sendReply(const std::string &msg) const
{
	std::string fullMsg = msg + "\r\n";
	ssize_t bytes = write(_fd, fullMsg.c_str(), fullMsg.size());

	if (bytes == -1)
		std::cerr << "Erreur lors de l'envoi à fd " << _fd << " : " << strerror(errno) << std::endl;
}
