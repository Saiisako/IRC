
#include "Client.hpp"
#include "Commande.hpp"
#include "IRC.hpp"

// Execute command USER : // USER <username> 0 * :<description client>
void goToUser(std::vector<std::string> &parts, Client &client)
{

	if (client.isReadyToRegister())
		client.sendReply("Your profil is already create");

	if (parts.size() < 4 || parts[4][0] != ':')
		return (client.sendReply("Error Not enough parameters USER"));

	std::string user = parts[1];
	std::string hostname = parts[2];
	std::string servername = parts[3];
	std::string realname = parts[4].substr(1);

	if (isValidname(user, client) == false)
		return ;
	if (hostname != "0")
		return (client.sendReply("Error hostname"));
	if (servername != "*")
		return (client.sendReply("Error servername"));
	for (unsigned i = 5; i < parts.size(); i++)
		realname += ' ' + parts[i];
	client.setUserName(user);
	client.setRealName(realname);
	client.setRegistredUser();
	if (client.getRegistredNick() == false)
		client.sendReply("add Nick for valid the all profil client");
	if (client.getRegistredUser() == true && client.getRegistredNick() == true)
		client.sendReply("Your profil is create");
	return ;
}

// ajouter controle du serveur si User est deja utilise dans la liste
