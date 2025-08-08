
// Client -> (envoie une ligne) -> Server -> analyse ligne -> Command
//-> appelle la bonne fonction

#pragma once

#include <string>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cerrno>
#include <set>

class Client
{
	private:
		int _fd;
		std::string _nickname;
		std::string _username;
		std::string _realname;
		bool _registredNick;
		bool _registredUser;
		bool _registredPassWord;
		bool _welcomeSent;

	public:
		Client(int fd);
		~Client();
		int getFd() const;
		std::string getNickName() const;
		std::string getUserName() const;
		std::string getRealName() const;
		bool getRegistredNick() const;
		bool getRegistredUser() const;
		bool getRegistredPassWord() const;
		void setNickname(const std::string &nick);
		void setUserName(const std::string &user);
		void setRealName(const std::string &realname);
		void setRegistredNick();
		void setRegistredUser();
		void setRegistredPassWord();
		bool isReadyToRegister() const;
		void sendReply(const std::string &msg) const;
		bool isWelcomeSent() const;
		void setWelcomeSent(bool b);

		bool operator==(const Client &other) const { return this->getFd() == other.getFd(); }
};

std::ostream &operator<<(std::ostream &flux, const Client &c);