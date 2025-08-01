
#include "Commande.hpp"
#include "Client.hpp"

bool isValidname(std::string &nick, client &client);

// Execute command : NICK <nickname> -> gives the client a nickname
bool goToNickName(std::vector<std::string> &parts, client &client)
{
	if (parts.size() < 2)
		return (client.sendReply("Error arguments NICK"), false);

	std::string nickname = parts[1];
	if (isValidname(nickname, client) == false)
		return false;

	client.setNickname(nickname);
	client.setRegistredNick();
	if (client.getRegistredUser() == false)
		client.sendReply("Add User for valid the all profil client");
	if (client.getRegistredUser() == true && client.getRegistredNick() == true)
		client.sendReply("Your profil is create");
	return true;
}

// ajouter controle du serveur pour voir si le surname est deja utilise dans la liste
