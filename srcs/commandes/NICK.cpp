
#include "Commande.hpp"
#include "Client.hpp"

// std::map<std::string, Client *> nicknameMap;

// Parsing string NickName
bool isValidNickname(std::string &nick)
{
	int i = 0;
	if (nick.empty())
		return false;

	while (nick[i])
	{
		if (!isalnum(nick[i]) && !isalpha(nick[i]))
		{
			std::cerr << "Error character Nickname" << std::endl;
			return (false);
		}
		if (i > 12)
		{
			std::cerr << "Error lenght" << std::endl;
			return (false);
		}
		i++;
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
	if (parts.size() < 2)
	{
		std::cerr << "Error arguments" << std::endl;
		return false;
	}
	std::string nickname = parts[1];

	if (isValidNickname(nickname) == false)
		return false;

	client->setNickname(nickname);
	std::cout << "NICK set to " << nickname << std::endl;

	return true;
}
