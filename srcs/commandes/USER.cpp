
#include "Client.hpp"
#include "Commande.hpp"

// Execute command USER : // USER <username> 0 * :<description client>
bool goToUser(std::vector<std::string> parts, client *client)
{
	if (parts.size() < 4 || parts[4][0] != ':')
		return (std::cerr << "Error Not enough parameters USER" << std::endl, false);

	std::string user = parts[1];
	std::string hostname = parts[2];
	std::string servername = parts[3];
	std::string realname = parts[4].substr(1);

	if (hostname != "0")
		return (std::cerr << "Error hostname" << std::endl, false);
	if (servername != "*")
		return (std::cerr << "Error servername" << std::endl, false);
	for (unsigned i = 5; i < parts.size(); i++)
		realname += ' ' + parts[i];

	client->setUserName(user);
	client->setRealName(realname);
	client->MakeAsRegistred();
	return true;
}
