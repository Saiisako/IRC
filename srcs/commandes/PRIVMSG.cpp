/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/08/11 18:55:14 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Commande.hpp"
#include "IRC.hpp"
#include "Error.hpp"

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

void	sendToClients(std::string msg, std::vector<Client> chanToSend, Client &client)
{
	for (std::vector<Client>::iterator it = chanToSend.begin(); it != chanToSend.end(); ++it)
	{
		std::ostringstream msg_pattern;
		msg_pattern << client.getNickName() << "!" << client.getUserName() << "@localhost " << "PRIVMSG " << msg << std::endl;
		std::string final_msg = msg_pattern.str();
		send(it->getFd(), final_msg.c_str(), final_msg.size(), 0);
	}
}

// void	sendToChannel(std::string msg, std::vector<Channel> chanToSend)
// {
// 	for (std::vector<Channel>::iterator it = chanToSend.begin(); it != chanToSend.end(); ++it)
// 	{
		
// 	}

// }

void	removeDuplicates(int flag, std::vector<Channel> &channelsToSend, std::vector<Client> &clientsToSend)
{
	if (flag == 0)
	{
		for (std::vector<Client>::iterator it = clientsToSend.begin(); it != clientsToSend.end(); ++it)
		{
			for (std::vector<Client>::iterator it2 = it + 1; it2 != clientsToSend.end(); ++it2)
			{
				if (it->getNickName() == it2->getNickName())
					clientsToSend.erase(it2);
			}
		}
	}
	else
	{
		for (std::vector<Channel>::iterator it = channelsToSend.begin(); it != channelsToSend.end(); ++it)
		{
			for (std::vector<Channel>::iterator it2 = it + 1; it2 != channelsToSend.end(); ++it2)
			{
				if (it->getChannel() == it2->getChannel())
					channelsToSend.erase(it2);
			}
		}
	}
}

bool	goToPrivMsg(std::vector<std::string> parts, Client &client, std::vector<Channel> &channels, std::vector<Client *>& clients)
{
	
	static bool flag_channel = false, flag_nick = false;
	std::vector<Client>		clientToSend;
	std::vector<Channel>	chanToSend;


	if (parts[1][0] != ':')
		return (client.sendReply(ERR_NOTEXTTOSEND(parts[1])), 1);
		
	std::vector<std::string> receivers = split(parts[0], ',');
	for (std::vector<std::string>::iterator it = receivers.begin(); it != receivers.end(); ++it)
	{
		if (it->empty()) continue;

		std::string value = *it;

		if (value[0] == '#')
		{
			std::pair<bool, Channel *> v = verifChan(value, channels);
			if (v.first == true)
				chanToSend.push_back(*v.second);
			else
			{
				static bool flag_channel = false;
				if (flag_channel == false)
				{
					client.sendReply(ERR_NOSUCHCHANNEL(client.getNickName()));
					flag_channel = true;
				}
				continue ;
			}
		}
		else
		{
			std::pair<bool, Client *> v = verifClient(value, clients);
			if (v.first == true)
				clientToSend.push_back(*v.second);
			else
			{
				static bool flag_nick = false;
				if (flag_nick == false)
				{
					client.sendReply(ERR_NOSUCHNICK(client.getNickName()));
					flag_nick = true;
				}
				continue;
			}
		}
	}
	if (!clientToSend.empty())
	{
		removeDuplicates(0, chanToSend, clientToSend);
		sendToClients(parts[1], clientToSend, client);
	}
	// if (!chanToSend.empty())
	// {
	// 	removeDuplicates(1, chanToSend, clientToSend);
	// 	sendToChannel(parts[2], chanToSend);
	// }
	
	flag_nick = false, flag_channel = false; // Put the static variable as false to handle numerical replies again.
	return (false);
}