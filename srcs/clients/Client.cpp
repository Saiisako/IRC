
#include "Client.hpp"

client::client(int fd) : _fd(fd), _nickname(""), _username(""), _realname(""), _registred(false) {}
client::~client() {}

int client::getFd() const { return this->_fd; }
std::string client::getNickName() const { return this->_nickname; }
std::string client::getUserName() const { return _username; }
std::string client::getRealName() const { return _realname; }
bool client::getRegistred() const { return _registred; }

void client::setNickname(const std::string &nick) { this->_nickname = nick; }
void client::setUserName(const std::string &user) { _username = user; }
void client::setRealName(const std::string &realname) { _realname = realname; }
void client::MakeAsRegistred() { _registred = true; }
