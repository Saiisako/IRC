
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

public:
	client(int fd);
	~client();

	std::string getNickname() const;
	void setNickname(const std::string &nick);
	int getFd() const;
};

#endif
