/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:36:56 by skock             #+#    #+#             */
/*   Updated: 2025/08/09 17:34:05 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commande.hpp"
#include "IRC.hpp"

std::pair<bool, Channel *> verifChan(const std::string& value, std::vector<Channel>& channels)
{
	for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if (it->getChannel() == value)
			return std::make_pair(true, &(*it));
	}
	return std::pair<bool, Channel *>(false, NULL);
}

std::pair<bool, Client *> verifClient(const std::string& value, std::vector<Client *>& Clients)
{
	for (std::vector<Client *>::iterator it = Clients.begin(); it != Clients.end(); ++it)
	{
		if ((*it)->getNickName() == value)
			return std::make_pair(true, *it);
	}
	return std::pair<bool, Client *>(false, NULL);
}

void	sendToClients(std::string msg, std::vector<Client> chanToSend)
{
	for (std::vector<Client>::iterator it = chanToSend.begin(); it != chanToSend.end(); ++it)
	{
		send(it->getFd(), msg.c_str(), msg.size(), 0);
	}
}

// void	sendToChannel(std::string msg, std::vector<Channel> channelToSend)
// {
// 	for (std::vector<Channel>::iterator it = channelToSend.begin(); it != channelToSend.end(); ++it)
// 	{
		
// 	}

// }

bool	goToPrivMsg(std::vector<std::string> parts, Client &client, std::vector<Channel> &channels, std::vector<Client *>& clients)
{
	(void)client;
	(void)channels;
	(void)clients;
	std::vector<Channel> chanToSend;
	std::vector<Client> clientToSend;
	if (parts.size() == 1)
		exit(1); // numerical replies to put
	std::vector<std::string> receivers = split(parts[1], ',');
	for (std::vector<std::string>::iterator it = receivers.begin(); it != receivers.end(); ++it)
	{
		if (it->empty()) continue;

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
	std::cout << "message to send "  << parts[2] << std::endl;
	sendToClients(parts[2], clientToSend);
	// sendToChannel(parts[2], chanToSend);
	std::cout << chanToSend[0].getUserList() << std::endl;
	return (false);
}