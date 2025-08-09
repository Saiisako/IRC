
#include "Commande.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "IRC.hpp"

/// mode #nom_du_canal [+/-modes] [paramètres]

static void useMode_i(std::vector<std::string> parts, Client &client, std::vector<Channel> &channels, std::vector<Client *>& clients)
{
	(void)parts;
	(void)client;
	std::cout << channels[0].getChannel() << std::endl;
	std::cout << clients[0]->getNickName() << std::endl;
}

// Vérifier que :

// le canal existe

// l’utilisateur est dans le canal

// l’utilisateur est opérateur du canal

bool goToMode(std::vector<std::string> parts, Client &client, std::vector<Channel> &channels, std::vector<Client *>& clients)
{
	std::string name_channel = parts[1];
	std::string mode = parts[2];
	std::string parametre;

	for (unsigned int i = 0; i < parts.size(); i++)
		std::cout << parts[i] << std::endl;

	std::cout << std::endl;
	std::cout << name_channel << std::endl;
	std::cout << mode << std::endl
			  << std::endl;

	// if (name_channel[0] != '#' && name_channel[0] != '$')
	//	return (client.sendReply("Error name channel" + name_channel[0]), false);
	// if (mode[0] != '+' || mode[0] != '-')
	//	return (client.sendReply("Error mode"), false);
	if (mode == "+i")
		useMode_i(parts, client, channels, clients);
	// passer en mode invite";

	//	Vérifier que :

	// le canal existe

	// l’utilisateur est dans le canal

	// l’utilisateur est opérateur du canal

	// Activer le mode +i dans ton objet Channel :
	return true;
}

// Les utilisateurs normaux(sans @)
// You’re not channel operator

// ◦ MODE - Changer le mode du channel :
// — i : Définir/supprimer le canal sur invitation uniquement
// 6
// ft_irc Internet Relay Chat
// — t : Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
// — k : Définir/supprimer la clé du canal (mot de passe)
// — o : Donner/retirer le privilège de l’opérateur de canal
// — l : Définir/supprimer la limite d’utilisateurs pour le canal
// • Bien entendu, on attend de vous un code propre.
