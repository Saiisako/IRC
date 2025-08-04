
#include "Commande.hpp"
#include "Client.hpp"

//'-' | '[' | ']' | '\' | '`' | '^' | '{' | '}'

bool special_char(char c)
{
	if (c == '-' || c == '[' || c == ']' || c == '\\' || c == '`' || c == '^' || c == '{' || c == '}')
		return true;
	return false;
}

// Parsing string name
bool isValidname(std::string &nick, client &client)
{
	if (nick.empty())
		return false;

	if (!isalpha(nick[0]))
		return (client.sendReply("Error character Nick or user " + nick), false);
	for (unsigned i = 1; nick[i]; i++)
	{
		if (!isalpha(nick[i]) && !isalnum(nick[i]) && special_char(nick[i]) && nick[i] != '\n')
			return (client.sendReply("Error character Nick or user " + nick), false);
		if (i > 9)
			return (client.sendReply("Error lenght"), false);
	}
	return true;
}
