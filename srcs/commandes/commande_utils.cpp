
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
// #define ERR_NONICKNAMEGIVEN(nick) "431 " + nick + " :No nickname given\n"

//// Returned after receiving a NICK message which contains characters which do not fall in the defined set.
// #define ERR_ERRONEUSNICKNAME(nick) "432 " + nick + " :Erroneus nickname\n"

//// Returned when a NICK message is processed that results in an attempt to change to a currently existing nickname.
// #define ERR_NICKNAMEINUSE(nick) "433 " + nick + " :Nickname is already in use\n"
