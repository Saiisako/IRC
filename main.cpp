/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:06:35 by skock             #+#    #+#             */
/*   Updated: 2025/08/08 15:07:11 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Commande.hpp"
#include "Channel.hpp"
#include "IRC.hpp"
#include "Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
		return (std::cerr << "Usage: ./ircserv <port> <password>" << std::endl, 1);
	else
	{
		Server server(av[2], av[1]);

		parse_port(av[1]);
		server.boot();
		server.run();
	}
}
