/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelecoq <jelecoq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:06:35 by skock             #+#    #+#             */
/*   Updated: 2025/07/30 16:25:05 by jelecoq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Commande.hpp"

// int main(int argc, char **argv)
//{
//	if (argc == 1)
//		return 1;
//	client testClient(1);
//	std::string input = argv[1];
//	if (commande::executeCommand(input, &testClient) == false)
//		return (1);

//	std::cout << "Nickname actuel : " << testClient.getNickName() << std::endl;
//	return 0;
//}

#include <iostream>
#include <vector>
#include <map>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <poll.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <cstdlib>

#define BUFFER_SIZE 1024

int makeSocketNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1)
		return -1;
	return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./server <port>" << std::endl;
		return 1;
	}
	int port = atoi(argv[1]);

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		std::cerr << "Erreur création socket" << std::endl;
		return 1;
	}

	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(server_fd, (sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		std::cerr << "Erreur bind" << std::endl;
		return 1;
	}

	if (listen(server_fd, 10) < 0)
	{
		std::cerr << "Erreur listen" << std::endl;
		return 1;
	}

	makeSocketNonBlocking(server_fd);

	std::vector<struct pollfd> fds;
	struct pollfd server_pollfd;
	server_pollfd.fd = server_fd;
	server_pollfd.events = POLLIN;
	server_pollfd.revents = 0;
	fds.push_back(server_pollfd);

	std::map<int, client> clients;

	char buffer[BUFFER_SIZE];
	std::cout << "Serveur en attente sur le port " << port << "..." << std::endl;

	while (true)
	{
		int ret = poll(&fds[0], fds.size(), -1);
		if (ret < 0)
		{
			std::cerr << "Erreur poll" << std::endl;
			break;
		}

		for (size_t i = 0; i < fds.size(); ++i)
		{
			if (fds[i].revents & POLLIN)
			{
				if (fds[i].fd == server_fd)
				{
					// Nouvelle connexion
					sockaddr_in client_addr;
					socklen_t client_len = sizeof(client_addr);
					int client_fd = accept(server_fd, (sockaddr *)&client_addr, &client_len);
					if (client_fd >= 0)
					{
						makeSocketNonBlocking(client_fd);

						struct pollfd new_pollfd;
						new_pollfd.fd = client_fd;
						new_pollfd.events = POLLIN;
						new_pollfd.revents = 0;
						fds.push_back(new_pollfd);

						clients.insert(std::make_pair(client_fd, client(client_fd)));

						std::cout << "Nouveau client connecté (fd=" << client_fd << ")" << std::endl;
					}
				}
				else
				{
					// Données d’un client existant
					memset(buffer, 0, BUFFER_SIZE);
					int bytes_received = recv(fds[i].fd, buffer, BUFFER_SIZE - 1, 0);
					if (bytes_received <= 0)
					{
						std::cout << "Client déconnecté (fd=" << fds[i].fd << ")" << std::endl;
						close(fds[i].fd);
						clients.erase(fds[i].fd);
						fds.erase(fds.begin() + i);
						--i;
						continue;
					}

					std::string input(buffer);
					std::map<int, client>::iterator it = clients.find(fds[i].fd);
					if (it != clients.end())
					{
						client &currentClient = it->second;

						if (!commande::executeCommand(input, &currentClient))
						{
							std::cerr << "Commande invalide ou erreur (fd=" << fds[i].fd << ")" << std::endl;
							continue;
						}

						std::cout << "Client fd=" << fds[i].fd << std::endl
								  << std::endl
								  << " Nickname: " << currentClient.getNickName() << std::endl
								  << " Username: " << currentClient.getUserName() << std::endl
								  << " Realname: " << currentClient.getRealName() << std::endl;
					}
				}
			}
		}
	}

	// Nettoyage
	for (size_t i = 0; i < fds.size(); ++i)
		close(fds[i].fd);

	return 0;
}
