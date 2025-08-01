
#include "Client.hpp"
#include "Commande.hpp"

bool isValidname(std::string &user, client &client);

// Execute command USER : // USER <username> 0 * :<description client>
bool goToUser(std::vector<std::string> &parts, client &client)
{
	if (parts.size() < 4 || parts[4][0] != ':')
		return (client.sendReply("Error Not enough parameters USER"), false);

	std::string user = parts[1];
	std::string hostname = parts[2];
	std::string servername = parts[3];
	std::string realname = parts[4].substr(1);

	if (isValidname(user, client) == false)
		return (false);
	if (hostname != "0")
		return (client.sendReply("Error hostname"), false);
	if (servername != "*")
		return (client.sendReply("Error servername"), false);
	for (unsigned i = 5; i < parts.size(); i++)
		realname += ' ' + parts[i];

	client.setUserName(user);
	client.setRealName(realname);
	client.setRegistredUser();
	if (client.getRegistredNick() == false)
		client.sendReply("add Nick for valid the all profil client");
	if (client.getRegistredUser() == true && client.getRegistredNick() == true)
		client.sendReply("Your profil is create");
	return true;
}

// ajouter controle du serveur si User est deja utilise dans la liste
