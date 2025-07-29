
#include "Client.hpp"

client::client(int fd) : _fd(fd), _nickname("") {}
client::~client() {}

std::string client::getNickname() const { return this->_nickname; }
int client::getFd() const { return this->_fd; }

void client::setNickname(const std::string &nick)
{
	this->_nickname = nick;
}
