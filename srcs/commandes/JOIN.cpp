// La commande /join te permet d'aller sur un channel. Il ne faut pas oublier le # pour un channel du réseau, le & pour un channel du serveur, ou enfin le +. De plus si le channel est protégé par une clef (mode +k), vous devez spécifier la clef après le nom du channel. Si le channel n'existe pas, un channel de ce nom sera créé et tu deviendra automatiquement opérateur.
// Syntaxe : /join <channel> [clef]
// Example : /join #cool
// Example : /join #franco_cool COOLCLEF

#include "Commande.hpp"
#include "Client.hpp"
#include "Channel.hpp"

bool isValidname(std::string &user, client *client);

// client join a channel
bool goToJoin(std::vector<std::string> parts, client *client)
{
	if (parts.size() < 2)
		return (client->sendReply("Error arguments Join"), false);

	if (client->isReadyToRegister() == false)
		return (client->sendReply("Error User not registred"), false);

	std::string name_channel = parts[1];
	std::string namechannel = name_channel.substr(1);

	if (name_channel[0] != '#' || name_channel[0] != '&')
		return (client->sendReply("Error : first charactere channel"), false);

	if (isValidname(namechannel, client) == false)
		return false;

	return true;
}
