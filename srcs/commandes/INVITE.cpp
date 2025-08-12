#include "IRC.hpp"

// INVITE Bob #42
bool goToInvite(std::vector<std::string> parts, Client &client, std::vector<Channel> &channels, std::vector<Client *> &clients)
{
	if (parts.size() < 3)
		return (client.sendReply(ERR_NEEDMOREPARAMS(parts[0])), false);

	std::string name_user = parts[1];
	std::string name_channel = parts[2];
	Channel *chan = NULL;
	if (name_channel[0] != '#')
		return (client.sendReply(""), false);

	for (unsigned int i = 0; i < channels.size(); i++)
	{
		if (channels[i].getChannel() == name_channel)
		{
			chan = &channels[i];
			break;
		}
	}
	if (!chan)
		return (client.sendReply(ERR_NOSUCHCHANNEL(name_channel)), false);
	if (!chan->isOperator(client.getNickName()))
		return (client.sendReply(ERR_CHANOPRIVSNEEDED(name_channel)), false);
	chan->addInvite(name_user);

	Client *targetClient = NULL;

	for (unsigned int i = 0; i < clients.size(); i++)
	{
		if (clients[i]->getNickName() == name_user)
		{
			targetClient = clients[i];
			break;
		}
	}
	if (targetClient)
	{
		client.sendReply(RPL_INVITING(name_user, name_channel));
		targetClient->sendReply(":" + client.getNickName() + " INVITE " + name_user + " " + name_channel);
	}
	return true;
}
