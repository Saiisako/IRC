
#include "Commande.hpp"
#include "Client.hpp"
#include "IRC.hpp"

//'-' | '[' | ']' | '\' | '`' | '^' | '{' | '}'

bool special_char(char c)
{
	if (c == '-' || c == '[' || c == ']' || c == '\\' || c == '`' || c == '^' || c == '{' || c == '}')
		return true;
	return false;
}

// Parsing string name
bool isValidname(std::string &nick, Client &client)
{
	if (nick.empty() || nick == "")
		return (client.sendReply(": serveur 431	* :ERR_NONICKNAMEGIVEN"), false);

	if (!isalpha(nick[0]))
		return (client.sendReply(": serveur 432" + nick + "ERR_ERRONEUSNICKNAME"), false);
	for (unsigned i = 1; nick[i]; i++)
	{
		if (!isalpha(nick[i]) && !isalnum(nick[i]) && !special_char(nick[i]) && nick[i] != '\n')
			return (client.sendReply(": serveur 432" + nick + "ERR_ERRONEUSNICKNAME"), false);
		if (i > 9)
			return (client.sendReply(": serveur 432" + nick + "ERR_ERRONEUSNICKNAME"), false);
	}
	return true;
}
