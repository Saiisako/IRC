
#include "IRC.hpp"


static bool verif_line(std::string &name_channel, std::string &mode, Client &client)
{
	if (name_channel.empty() && name_channel[0] != '#')
	{
		client.sendReply(ERR_BADCHANNAME(client.getNickName(), name_channel));
		return false;
	}
	if (mode.empty() || mode.size() != 2)
	{
		client.sendReply(ERR_UNKNOWNMODE(mode));
		return false;
	}
	if ((mode[0] != '+' && mode[0] != '-') || (mode[1] != 'i' && mode[1] != 't' && mode[1] != 'k' && mode[1] != 'o' && mode[1] != 'l'))
	{
		client.sendReply(ERR_UNKNOWNMODE(mode));
		return false;
	}
	return true;
}


static bool verif_parametre(std::vector<std::string> parts, std::string &parametre, Client &client, std::string &name_channel)
{
	if (parametre.empty())
	{
		client.sendReply(ERR_NEEDMOREPARAMS(parts[0]));
		return false;
	}
	for (unsigned int i = 0; i < parametre.size(); i++)
	{
		if (!isdigit(parametre[i]))
		{
			client.sendReply(ERR_INVALIDLIMIT(name_channel));
			return false;
		}
	}
	return true;
}

bool goToMode(std::vector<std::string> parts, Client &client, std::vector<Channel *> &channels, std::vector<Client *> &clients)
{
	std::string parametre;
	(void)clients;
	if (parts.size() < 3)
	{
		client.sendReply(ERR_NEEDMOREPARAMS(parts[0]));
		return false;
	}
	std::string name_channel = parts[1];
	std::string mode = parts[2];
	if (!verif_line(name_channel, mode, client))
		return false;
	if (parts.size() == 4)
		parametre = parts[3];
	Channel *targetChannel = NULL;
	for (unsigned int i = 0; i < channels.size(); i++)
	{
		if (channels[i]->getChannel() == name_channel)
		{
			targetChannel = channels[i];
			break;
		}
	}
	if (!targetChannel)
	{
		client.sendReply(ERR_NOSUCHCHANNEL(name_channel));
		return false;
	}
	if (targetChannel->getOperator() != client.getNickName())
	{
		client.sendReply(ERR_CHANOPRIVSNEEDED(client.getNickName()));
		return false;
	}
	bool active = (mode[0] == '+');
	switch (mode[1])
	{
	case 'i': targetChannel->setInviteOnly(active); break;
	case 't': targetChannel->setTopicOperator(active); break;
	case 'k': targetChannel->setPassWord(active); break;
	case 'o':
		if (active)
			targetChannel->addOperator(parametre);
		else
			targetChannel->removeOperator(parametre);
		break;
	case 'l':
		if (active)
		{
			if (!verif_parametre(parts, parametre, client, name_channel))
				return false;
			int limite = atoi(parametre.c_str());
			targetChannel->setLimiteUserChannel(limite);
			targetChannel->setLimiteUserIsActive(true);
		}
		else
			targetChannel->setLimiteUserIsActive(false);
		break;
	default:
		client.sendReply(ERR_UNKNOWNMODE(mode));
		return false;
	}
	print_channel(client, targetChannel);
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
