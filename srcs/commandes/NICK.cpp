
#include "Commande.hpp"
#include "Client.hpp"
#include "IRC.hpp"
#include "Error.hpp"

// Execute command : NICK <nickname> -> change the client nickname after the client is set
bool goToNickName(std::vector<std::string> &parts, Client &client, std::vector<Client> &clients)
{
	if (parts.size() < 2)
		return (client.sendReply(ERR_NEEDMOREPARAMS(parts[0])), false);
	std::string nickname = parts[1];
	if (isValidname(nickname, client) == false)
		return false;

	if (client.getRegistredUser() == false)
		client.sendReply("Add User for valid the all profil client");
	else if (client.getRegistredNick() == true)
		client.sendReply("Your nickname has been changed");
	client.setNickname(nickname);
	client.setRegistredNick();
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		if (clients[i].getNickName() == client.getNickName())
		{
			std::cout << "CLIENT NICK " << clients[i].getNickName() << std::endl;
			return (client.sendReply(ERR_NICKNAMEINUSE(client.getNickName())), false);
		}
	}
	return true;
}
// regarder si le nick a deja ete utiliser par un autre client

// Code	Nom symbolique	Signification
// 431	ERR_NONICKNAMEGIVEN	Aucun pseudonyme n’a été fourni dans la commande NICK.
// 432	ERR_ERRONEUSNICKNAME	Le pseudonyme est invalide (caractères interdits ou format incorrect).
// 433	ERR_NICKNAMEINUSE	Le pseudonyme est déjà utilisé par un autre utilisateur.
// Returned when a nickname parameter expected for a command and isn't found.
