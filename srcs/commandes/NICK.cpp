

#include "IRC.hpp"

static bool special_char(char c)
{
	if (c == '-' || c == '[' || c == ']' || c == '\\' || c == '`' || c == '^' || c == '{' || c == '}')
		return true;
	return false;
}

// Parsing string name
static bool isValidname(std::string &nick, Client &client)
{
	if (nick.empty() || nick == "")
		return (client.sendReply(ERR_NONICKNAMEGIVEN(nick)), false);

	if (!isalpha(nick[0]))
		return (client.sendReply(ERR_ERRONEUSNICKNAME(nick)), false);
	for (unsigned i = 1; nick[i]; i++)
	{
		if (!isalnum(nick[i]) && !special_char(nick[i]) && nick[i] != '\n')
			return (client.sendReply(ERR_ERRONEUSNICKNAME(nick)), false);
		if (i > 9)
			return (client.sendReply(ERR_ERRONEUSNICKNAME(nick)), false);
	}
	return true;
}

// Execute command : NICK <nickname> -> change the client nickname after the client is set
bool goToNickName(std::vector<std::string> &parts, Client &client, std::vector<Client *> &clients)
{
	if (parts.size() < 2)
		return (client.sendReply(ERR_NEEDMOREPARAMS(parts[0])), false);
	std::string nickname = parts[1];
	if (isValidname(nickname, client) == false)
		return false;

	// if (client.getRegistredUser() == false)
	//	client.sendReply("Add User for valid the all profil client");
	// else if (client.getRegistredNick() == true)
	//	client.sendReply("Your nickname has been changed");
	client.setNickname(nickname, clients, client);
	client.setRegistredNick();
	return true;
}
