
#include "Commande.hpp"
#include "Client.hpp"

// std::map<std::string, Client *> nicknameMap;

// Parsing string NickName
static bool isValidNickname(std::string &nick)
{
	if (nick.empty())
		return false;

	for (unsigned i = 0; nick[i]; i++)
	{
		if (!isalnum(nick[i]) && !isalpha(nick[i]) && nick[i] != '\n')
			return (std::cerr << "Error character Nickname " << nick << std::endl, false);
		if (i > 12)
			return (std::cerr << "Error lenght" << std::endl, false);
	}
	// if (nicknameMap.find(nick) != nicknameMap.end())
	//{
	//	std::cerr << "Error Nickname is already in use" << std::endl;
	//	return (false);
	// }
	return true;
}

// Execute command NICK -> gives the client a nickname
bool goToNickName(std::vector<std::string> &parts, client *client)
{

	if (client->getRegistred() == true)
		return (std::cerr << "Error USER already registred" << std::endl, false);

	if (parts.size() < 2)
		return (std::cerr << "Error arguments NICK" << std::endl, false);

	std::string nickname = parts[1];
	if (isValidNickname(nickname) == false)
		return false;

	client->setNickname(nickname);
	return true;
}
