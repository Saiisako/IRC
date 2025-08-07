
#include "Client.hpp"
#include "Commande.hpp"
#include "IRC.hpp"

// Execute command USER : // USER <username> 0 * :<description client>
bool goToUser(std::vector<std::string> &parts, Client &client)
{

	if (client.isReadyToRegister())
		client.sendReply(":462 ERR_ALREADYREGISTRED");

	if (parts.size() <= 4 || parts[4][0] != ':')
		return (client.sendReply(":461	ERR_NEEDMOREPARAMS"), false);

	std::string user = parts[1];
	std::string hostname = parts[2];
	std::string servername = parts[3];
	std::string realname = parts[4].substr(1);

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
	return true;
}

// regarder si User est deja utilise par un autre client

// Code	Nom symbolique	Signification
// 461	ERR_NEEDMOREPARAMS	Commande USER mal formée — il manque un ou plusieurs paramètres.
// 462	ERR_ALREADYREGISTRED	Le client a déjà terminé sa phase d’enregistrement (NICK + USER). Il ne peut pas refaire la commande USER.
