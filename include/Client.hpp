
// Client -> (envoie une ligne) -> Server -> analyse ligne -> Command
//-> appelle la bonne fonction

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cerrno>

class client
{
private:
	int _fd;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	bool _registredNick;
	bool _registredUser;

public:
	client(int fd);
	~client();

	int getFd() const;
	std::string getNickName() const;
	std::string getUserName() const;
	std::string getRealName() const;
	bool getRegistredNick() const;
	bool getRegistredUser() const;

	void setNickname(const std::string &nick);
	void setUserName(const std::string &user);
	void setRealName(const std::string &realname);
	void setRegistredNick();
	void setRegistredUser();

	bool isReadyToRegister() const;

	void sendReply(const std::string &msg) const;
};

#endif
