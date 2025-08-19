/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelecoq <jelecoq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 01:41:28 by skock             #+#    #+#             */
/*   Updated: 2025/08/19 12:27:06 by jelecoq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commande.hpp"
#include "IRC.hpp"
#include "Error.hpp"

bool	DoesClientExistOnServer(std::vector<Client *> &clients, std::string &nick)
{
	bool	found = false;
	for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if ((*it)->getNickName() == nick)
			return (true);
	}
	if (!found)
		return (false);
	return (false);
}

bool DoesClientExistOnChan(std::vector<Client *> &clients, std::vector<Channel *> &channels, const std::string &nick)
{
	Client *tmp = NULL;

	for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if ((*it)->getNickName() == nick)
		{
			tmp = *it;
			break;
		}
	}
	if (!tmp)
		return (false);

	for (std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if ((*it)->hasClient(*tmp))
			return (true);
	}

	return (false);
}


// KICK <channel> <user> [<comment>]
bool goToKick(std::vector<std::string> parts, Client &client, std::vector<Channel *> &channels, std::vector<Client *> &clients)
{
	bool	allowedToSend = false;
	for ( std::vector<Channel *>::iterator it = channels.begin(); it != channels.end(); ++it)
	{
		if ((*it)->getChannel() == parts[1])
		{
			if ((*it)->getOperator() == client.getNickName())
			{
				allowedToSend = true;
				break ;
			}
			else
			{
				client.sendReply(ERR_CHANOPRIVSNEEDED(client.getNickName(), (*it)->getChannel()));
				return (false);
			}
		}
	}
	if (allowedToSend == true)
	{
		if (DoesClientExistOnServer(clients, parts[1]) == true)
		{
			if (DoesClientExistOnChan(clients, channels, parts[1]) == true)
			{
				//KICKHERE
			}
			else
			{
				client.sendReply(ERR_USERNOTINCHANNEL(parts[1], parts[0]));
				return (false);
			}
		}
		else
		{
			client.sendReply(ERR_NOSUCHNICK(client.getServerName(), client.getNickName(), parts[1]));
			return (false);
		}
	}
	else
	{
		client.sendReply(ERR_NOSUCHCHANNEL(parts[0]));
		return (false);
	}

	return true;
}
