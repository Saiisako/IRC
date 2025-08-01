
#include "Commande.hpp"
#include "Client.hpp"

// Parsing string name
bool isValidname(std::string &nick, client &client)
{
	if (nick.empty())
		return false;

	for (unsigned i = 0; nick[i]; i++)
	{
		if (!isalnum(nick[i]) && !isalpha(nick[i]) && nick[i] != '\n')
			return (client.sendReply("Error character Nick or user " + nick), false);
		if (i > 12)
			return (client.sendReply("Error lenght"), false);
	}
	return true;
}
