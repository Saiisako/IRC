#include "IRC.hpp"

// INVITE Bob #42
bool goToInvite(std::vector<std::string> parts, Client &client, std::vector<Channel *> &channels, std::vector<Client *> &clients)
{
	if (parts.size() < 3)
	{
		client.sendReply(ERR_NEEDMOREPARAMS(parts[0]));
		return false;
	}
	std::string name_user = parts[1];
	std::string name_channel = parts[2];
	Channel *chan = NULL;
	if (name_channel[0] != '#')
	{
		client.sendReply("error ");
		return false;
	}

	for (unsigned int i = 0; i < channels.size(); i++)
	{
		if (channels[i]->getChannel() == name_channel)
		{
			chan = channels[i];
			break;
		}
	}
	if (!chan)
	{
		client.sendReply(ERR_NOSUCHCHANNEL(name_channel));
		return false;
	}
	if (!chan->isOperator(client.getNickName()))
	{
		client.sendReply(ERR_CHANOPRIVSNEEDED(name_channel));
		return false;
	}
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
