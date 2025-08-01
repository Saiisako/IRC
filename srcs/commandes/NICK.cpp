
#include "Commande.hpp"
#include "Client.hpp"

bool isValidname(std::string &nick, client &client);

// Execute command : NICK <nickname> -> gives the client a nickname
bool goToNickName(std::vector<std::string> &parts, client &client)
{
	if (client.isReadyToRegister())
		client.sendReply("Your profil is already create");

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

// bool goToNickName(std::vector<std::string> &parts, client &client)
//{
// std::string nickname = parts[1];

//// [2] Hopcount fourni par erreur → ignoré
//// Rien à faire ici car on ignore [<hopcount>]

//// [3] Nick invalide
// if (!isValidname(nickname, client))
//{
//	client.sendReply("432 * " + nickname + " :Erroneous nickname"); // ERR_ERRONEUSNICKNAME
//	return false;
// }

//// [4] Vérification des collisions locales
// for (std::vector<client>::iterator it = clients.begin(); it != clients.end(); ++it)
//{
//	if (it->getFd() != client.getFd() && it->getNickname() == nickname)
//	{
//		// Si c’est une tentative de changement de nick vers un nick déjà pris → collision
//		if (client.isRegistered())
//		{
//			client.sendReply("436 * " + nickname + " :Nickname collision"); // ERR_NICKCOLLISION
//			return false;
//		}
//		else
//		{
//			client.sendReply("433 * " + nickname + " :Nickname is already in use"); // ERR_NICKNAMEINUSE
//			return false;
//		}
//	}
// }

//// [5] Diffuser le changement de nick si enregistré
// if (client.isRegistered() && client.getNickname() != "")
//{
//	std::string oldNick = client.getNickname();
//	client.setNickname(nickname);
//	broadcastToAllClients(":" + oldNick + " NICK :" + nickname, clients, client);
// }
// else
//{
//	client.setNickname(nickname);
//	client.setRegisteredNick();
// }

//// [6] Vérifie si l’utilisateur peut maintenant être considéré comme "registré"
// if (client.getRegisteredUser() && client.getRegisteredNick())
//{
//	client.markAsFullyRegistered(); // à implémenter
//	client.sendWelcome(); // :server 001 nick :Welcome to the IRC Network ...
// }

// return true;
// }
