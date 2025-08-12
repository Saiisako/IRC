/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelecoq <jelecoq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/08/12 19:04:28 by jelecoq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commande.hpp"
#include "IRC.hpp"
#include "Error.hpp"

std::pair<bool, Channel *> verifChan(const std::string &value, std::vector<Channel> &channels)
{
	for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if (it->getChannel() == value)
			return std::make_pair(true, &(*it));
	}
	return std::pair<bool, Channel *>(false, NULL);
}

std::pair<bool, Client *> verifClient(const std::string &value, std::vector<Client *> &Clients)
{
	for (std::vector<Client *>::iterator it = Clients.begin(); it != Clients.end(); ++it)
	{
		if ((*it)->getNickName() == value)
			return std::make_pair(true, *it);
	}
	return std::pair<bool, Client *>(false, NULL);
}

void sendToClients(std::string msg, std::vector<Client> chanToSend, Client &client)
{
	for (std::vector<Client>::iterator it = chanToSend.begin(); it != chanToSend.end(); ++it)
	{
		std::ostringstream msg_pattern;
		msg_pattern << client.getNickName() << "!" << client.getUserName() << "@localhost " << "PRIVMSG " << msg;
		std::string final_msg = msg_pattern.str();
		send(it->getFd(), final_msg.c_str(), final_msg.size(), 0);
	}
}

// void	sendToChannel(std::string msg, std::vector<Channel> channelToSend)
// {
// 	for (std::vector<Channel>::iterator it = channelToSend.begin(); it != channelToSend.end(); ++it)
// 	{

// 	}

// }

bool goToPrivMsg(std::vector<std::string> parts, Client &client, std::vector<Channel> &channels, std::vector<Client *> &clients)
{
	std::vector<Channel> chanToSend;
	std::vector<Client> clientToSend;
	if (parts.size() == 1)
		return (client.sendReply(ERR_NORECIPIENT(parts[1])), 1);
	else if (parts[1][0] == ':')
		return (client.sendReply(ERR_NORECIPIENT(parts[1])), 1);
	if (parts.size() < 3)
		return (client.sendReply(ERR_NOTEXTTOSEND(parts[1])), 1);
	else if (parts[2][0] != ':')
		return (client.sendReply(ERR_NOTEXTTOSEND(parts[1])), 1);
	std::vector<std::string> receivers = split(parts[1], ',');
	for (std::vector<std::string>::iterator it = receivers.begin(); it != receivers.end(); ++it)
	{
		if (it->empty())
			continue;

		std::string value = *it;

		if (value[0] == '#')
		{
			std::pair<bool, Channel *> v = verifChan(value, channels);
			if (v.first == true)
				chanToSend.push_back(*v.second);
		}
		else
		{
			std::pair<bool, Client *> v = verifClient(value, clients);
			if (v.first == true)
				clientToSend.push_back(*v.second);
		}
	}
	std::string message;
	for (size_t i = 2; i < parts.size(); ++i)
		message += " " + parts[i];
	sendToClients(message, clientToSend, client);
	// sendToChannel(parts[2], chanToSend);
	return (false);
}
