
#include "Commande.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "IRC.hpp"

/// mode #nom_du_canal [+/-modes] [paramètres]

static void useMode_i(std::vector<std::string> parts, Client &client, std::vector<Channel> &channels, std::vector<Client> clients)
{
	(void)parts;
	(void)client;

	std::cout << channels[0].getChannel() << std::endl;
	std::cout << clients[0].getNickName() << std::endl;
}

// Vérifier que :

// le canal existe

// l’utilisateur est dans le canal

// l’utilisateur est opérateur du canal

// Activer le mode +i dans ton objet Channel :

bool goToMode(std::vector<std::string> parts, Client &client, std::vector<Channel> &channels, std::vector<Client> clients)
{
	if (parts.size() < 3)
		client.sendReply(ERR_NEEDMOREPARAMS(parts[0]));
	std::string name_channel = parts[1];
	std::string mode = parts[2];
	std::string parametre;
	for (unsigned int i = 0; i < channels.size(); i++)
	{
		if (channels[i].getChannel() != name_channel)
			client.sendReply(ERR_NOSUCHCHANNEL(name_channel));
		if (channels[i].getChannel() == name_channel && channels[i].getOperator() != client.getNickName())
			client.sendReply(ERR_CHANOPRIVSNEEDED(client.getNickName()));
	}

	if (mode == "+i")
		useMode_i(parts, client, channels, clients);
	// passer en mode invite";

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

// ERR_NEEDMOREPARAMS              RPL_CHANNELMODEIS
// ERR_CHANOPRIVSNEEDED            ERR_NOSUCHNICK
// ERR_NOTONCHANNEL                ERR_KEYSET
// RPL_BANLIST                     RPL_ENDOFBANLIST
// ERR_UNKNOWNMODE                 ERR_NOSUCHCHANNEL

// ERR_USERSDONTMATCH              RPL_UMODEIS
// ERR_UMODEUNKNOWNFLAG

// #define ERR_KEYSET(channel) "467 " + channel + " :Channel key already set\n"
// #define ERR_NOCHANMODES(channel) "477 " + channel + " :Channel doesn't support modes\n"
// #define ERR_UNKWOWNMODE(chare, channel) "472 " + chare + " :is unknown mode char to me for " + channel + "\n"
// #define RPL_BANLIST(channel, mask) "367 " + channel + " " + mask + "\n"
// #define RPL_ENDOFBANLIST(channel) "368 " + channel + " :End of channel ban list\n"
// #define RPL_EXCEPTLIST(channel, mask) "348 " + channel + " " + mask + "\n"
// #define RPL_ENDOFEXCEPTLIST(channel) "349 " + channel + " :End of channel exception list\n"
// #define RPL_INVITELIST(channel, mask) "346 " + channel + " " + mask + "\n"
// #define RPL_ENDOFINVITELIST(channel) "347 " channel " :End of channel invite list\n"
// #define RPL_UNIQOPIS(channel, nick) "325 " + channel + " " + nick + "\n"

// 461 ERR_NEEDMOREPARAMS       :Not enough parameters – the command requires more.
// 482 ERR_CHANOPRIVSNEEDED     :You're not a channel operator.
// 401 ERR_NOSUCHNICK           :No such nickname found.
// 442 ERR_NOTONCHANNEL         :You're not on that channel.
// 467 ERR_KEYSET               :Channel already has a key set.
// 367 RPL_BANLIST              :Ban list entry for the channel.
// 368 RPL_ENDOFBANLIST         :End of channel ban list.
// 472 ERR_UNKNOWNMODE          :Unknown mode flag.
// 403 ERR_NOSUCHCHANNEL        :That channel does not exist.
// 502 ERR_USERSDONTMATCH       :You can only change your own modes.
// 221 RPL_UMODEIS              :Your current user modes:
//{
//	modes
// }
// 501 ERR_UMODEUNKNOWNFLAG : Unknown user mode flag.

// #define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :That channel does not exist"
// #define ERR_CHANOPRIVSNEEDED(nick) "482 " + nick + " :You're not a channel operator"

// 461 ERR_NEEDMOREPARAMS       :Commande incomplète – il manque un ou plusieurs paramètres.
// 482 ERR_CHANOPRIVSNEEDED     :Vous devez être opérateur du canal pour faire cela.
// 401 ERR_NOSUCHNICK           :Ce pseudonyme n'existe pas.
// 442 ERR_NOTONCHANNEL         :Vous n’êtes pas sur ce canal.
// 467 ERR_KEYSET               :Une clé (mot de passe) est déjà définie sur ce canal.
// 367 RPL_BANLIST              :Utilisateur banni listé pour ce canal.
// 368 RPL_ENDOFBANLIST         :Fin de la liste des utilisateurs bannis du canal.
// 472 ERR_UNKNOWNMODE          :Mode inconnu ou non reconnu.
// 403 ERR_NOSUCHCHANNEL        :Ce canal n'existe pas.
// 502 ERR_USERSDONTMATCH       :Vous ne pouvez modifier que vos propres modes.
// 221 RPL_UMODEIS              :Vos modes utilisateur actuels sont : {modes}
// 501 ERR_UMODEUNKNOWNFLAG     :Drapeau de mode utilisateur inconnu.
