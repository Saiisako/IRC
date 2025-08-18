

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

	if (!isalpha(nick[0]))
	{
		client.sendReply(ERR_ERRONEUSNICKNAME(nick));
		return false;
	}

	for (unsigned i = 1; nick[i]; i++)
	{
		if (!isalnum(nick[i]) && !special_char(nick[i]) && nick[i] != '\n')
		{
			client.sendReply(ERR_ERRONEUSNICKNAME(nick));
			return false;
		}

		if (i > 9)
		{
			client.sendReply(ERR_ERRONEUSNICKNAME(nick));
			return false;
		}
	}
	return true;
}

// Execute command : NICK <nickname> -> change the client nickname after the client is set
bool goToNickName(std::vector<std::string> &parts, Client &client, std::vector<Client *> &clients)
{
	if (parts.size() < 1)
	{
		if (parts[0] == "NICK")
			client.sendReply(ERR_NONICKNAMEGIVEN(parts[0]));
		else
			client.sendReply(ERR_NEEDMOREPARAMS(parts[0]));
		return false;
	}
	std::string nickname = parts[1];
	if (!isValidname(nickname, client))
		return false;
	client.setNickname(nickname, clients, client);
	client.setRegistredNick();
	std::cout << client << std::endl;
	return true;
}
