
// Client -> (envoie une ligne) -> Server -> analyse ligne -> Command
//-> appelle la bonne fonction

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <iostream>

class client
{
private:
	int _fd;
	std::string _nickname;
	std::string _username;
	std::string _realname;
	bool _registred;

public:
	client(int fd);
	~client();

	int getFd() const;
	std::string getNickName() const;
	std::string getUserName() const;
	std::string getRealName() const;
	bool getRegistred() const;

	void setNickname(const std::string &nick);
	void setUserName(const std::string &user);
	void setRealName(const std::string &realname);

	void MakeAsRegistred();
};

#endif
