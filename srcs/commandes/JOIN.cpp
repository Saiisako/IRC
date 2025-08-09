// La commande /join te permet d'aller sur un channel. Il ne faut pas oublier le # pour un channel du réseau, le & pour un channel du serveur, ou enfin le +. De plus si le channel est protégé par une clef (mode +k), vous devez spécifier la clef après le nom du channel. Si le channel n'existe pas, un channel de ce nom sera créé et tu deviendra automatiquement opérateur.
// Syntaxe : /join <channel> [clef]
// Example : /join #cool
// Example : /join #franco_cool COOLCLEF

#include "Commande.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "IRC.hpp"

// client join a channel
bool goToJoin(std::vector<std::string> parts, Client &client, std::vector<Channel> &channels, std::vector<Client *>& clients)
{
	(void)clients;
	bool found = false;
	if (parts.size() < 2)
		return (client.sendReply(ERR_NEEDMOREPARAMS(parts[0])), false);

	if (client.isReadyToRegister() == false)
		return (client.sendReply(ERR_NOTREGISTERED), false);

	std::string name_channel = parts[1];
	std::string namechannel = name_channel.substr(1);

	if (name_channel[0] != '#' && name_channel[0] != '&')
		return (client.sendReply("Error : first charactere channel"), false);

	for (unsigned int i = 0; namechannel[i]; i++)
	{
		if (namechannel[i] == ',' || namechannel[i] == ':')
			return (client.sendReply(""), false);
	}

	for (unsigned int i = 0; i < channels.size(); i++)
	{
		if (channels[i].getChannel() == namechannel)
		{
			Channel &chan = channels[i];
			chan.addClient(client);
			std::cout << "CLIENT NICKNAME IN JOIN = [" << client.getNickName() << "]" << std::endl;
			std::string userList = chan.getUserList();
			std::cout << "USER LIST: " << userList << "\n";
			client.sendReply("Welcome, the list of users in the channel is: " + userList);
			chan.broadcast(client.getNickName() + " has joined the channel " + chan.getChannel(), client);
			found = true;
			break;
		}
	}
	if (!found)
	{
		Channel newChannel(namechannel);
		newChannel.addClient(client);
		newChannel.addOperator(client.getNickName());
		newChannel.setOperator(client.getNickName());
		client.sendReply(" You are the first to join the channel ");
		channels.push_back(newChannel);
	}
	std::cout << client.getNickName() << " has joined the channel " << namechannel << std::endl;

	return true;
}

// Code	Nom	Signification
// 403	ERR_NOSUCHCHANNEL	Le canal n’existe pas
// 405	ERR_TOOMANYCHANNELS	Le client a rejoint trop de canaux
// 471	ERR_CHANNELISFULL	Le canal est plein
// 472	ERR_UNKNOWNMODE ou ERR_INVITEONLYCHAN	Le canal est en mode "invite-only"
// 475	ERR_BADCHANNELKEY	Mauvais mot de passe (clé) pour rejoindre
// 474	ERR_BANNEDFROMCHAN	Le client est banni de ce canal
// 332	RPL_TOPIC	Le serveur envoie le topic du canal après avoir rejoint
