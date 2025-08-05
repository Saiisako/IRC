

// Code	Nom symbolique	Signification
// 461	ERR_NEEDMOREPARAMS	La commande PASS a été envoyée sans mot de passe. Exemple : PASS (vide ou incomplète).
// 462	ERR_ALREADYREGISTRED	Le client a déjà été enregistré (il a déjà envoyé NICK et USER). Il est alors trop tard pour envoyer ou modifier la commande PASS.

#include "Commande.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "IRC.hpp"

bool goToPass(std::string &password, std::vector<std::string> &parts, Client &client)
{
	if (client.isReadyToRegister() == true)
		return (client.sendReply(":serveur 462 * :ERR_ALREADYREGISTRED"), false);
	if (parts.size() < 2)
		return (client.sendReply(":serveur 461 * :NEEDMOREPARAMS"), false);
	std::string passwordClient = parts[1];
	if (password != passwordClient)
		return (client.sendReply(":serveur 464 * :ERR_PASSWORD"), false);
	client.setRegistredPassWord();
	return true;
}
