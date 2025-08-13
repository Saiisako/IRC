
#include "IRC.hpp"

// Execute command USER : // USER <username> 0 * :<description client>
bool goToUser(std::vector<std::string> &parts, Client &client)
{
	if (client.isReadyToRegister())
	{
		client.sendReply(ERR_ALREADYREGISTRED);
		return false;
	}
	if (parts.size() <= 4)
	{
		client.sendReply(ERR_NEEDMOREPARAMS(parts[0]));
		return false;
	}

	std::string user = parts[1];
	std::string hostname = parts[2];
	std::string servername = parts[3];
	std::string realname = parts[4].substr(1);

	if (parts[4][0] != ':')
	{
		client.sendReply("Error realname");
		return false;
	}
	if (hostname != "0")
	{
		client.sendReply("Error hostname");
		return false;
	}
	if (servername != "*")
	{
		client.sendReply("Error servername");
		return false;
	}
	for (unsigned i = 5; i < parts.size(); i++)
		realname += ' ' + parts[i];
	client.setUserName(user);
	client.setRealName(realname);
	client.setRegistredUser(true);
	return (true);
}

// regarder si User est deja utilise par un autre client

// Code	Nom symbolique	Signification
// 461	ERR_NEEDMOREPARAMS	Commande USER mal formée — il manque un ou plusieurs paramètres.
// 462	ERR_ALREADYREGISTRED	Le client a déjà terminé sa phase d’enregistrement (NICK + USER). Il ne peut pas refaire la commande USER.
