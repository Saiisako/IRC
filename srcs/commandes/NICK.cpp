
#include "Commande.hpp"
#include "Client.hpp"
#include "../../include/IRC.hpp"

// Execute command : NICK <nickname> -> change the client nickname after the client is set
bool goToNickName(std::vector<std::string> &parts, Client &client)
{
	if (parts.size() < 2)
		return (client.sendReply(":serveur 431 * :ERR_NONICKNAMEGIVEN"), false);
	std::string nickname = parts[1];
	if (isValidname(nickname, client) == false)
		return false;

	if (client.getRegistredUser() == false)
		client.sendReply("Add User for valid the all profil client");
	else if (client.getRegistredNick() == true)
		client.sendReply("Your nickname has been changed");
	client.setNickname(nickname);
	client.setRegistredNick();
	return true;
}
// regarder si le nick a deja ete utiliser par un autre client

// Code	Nom symbolique	Signification
// 431	ERR_NONICKNAMEGIVEN	Aucun pseudonyme n’a été fourni dans la commande NICK.
// 432	ERR_ERRONEUSNICKNAME	Le pseudonyme est invalide (caractères interdits ou format incorrect).
// 433	ERR_NICKNAMEINUSE	Le pseudonyme est déjà utilisé par un autre utilisateur.
