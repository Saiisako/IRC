/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:06:35 by skock             #+#    #+#             */
/*   Updated: 2025/07/30 17:12:02 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

int g_fd;
std::vector<int> clients;

void	serv_loop(void)
{
	while (1)
	{
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(g_fd, &readfds);
		int max_fd = g_fd;
		for (std::vector<int>::iterator it = clients.begin(); it != clients.end(); ++it)
		{
			FD_SET(*it, &readfds);
			if (*it > max_fd)
				max_fd = *it;
		}
		int activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);
		if (activity < 0)
		{
			std::cerr << "select problem" << std::endl;
			break;
		}
		if (FD_ISSET(g_fd, &readfds))
		{
			sockaddr_in client_addr;
			socklen_t addrlen = sizeof(client_addr);
			int client_fd = accept(g_fd, reinterpret_cast<sockaddr*>(&client_addr), &addrlen);
			if (client_fd >= 0)
			{
				clients.push_back(client_fd);
				std::cout << "New client connected: fd " << client_fd << std::endl;
			}
		}
		for (std::vector<int>::iterator it = clients.begin(); it != clients.end();)
		{
			int client_fd = *it;
			if (FD_ISSET(client_fd, &readfds))
			{
				char buffer[5];
				ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
				if (bytes <= 0)
				{
					close(client_fd);
					it = clients.erase(it);
					std::cout << "Client disconnected: fd " << client_fd << std::endl;
					continue;
				}
				buffer[bytes] = '\0';
				std::cout << "Received from fd " << client_fd << ": " << buffer << std::endl;
				send(client_fd, buffer, bytes, 0);
			}
			++it;
		}
	}
}

int	start_serv(int port, std::string password)
{
	(void)password;
	int bind_return;
	sockaddr_in	sst;
	memset(&sst.sin_zero, 0, sizeof(sst.sin_zero)); //
	sst.sin_family = AF_INET;
	sst.sin_addr.s_addr = htonl(INADDR_ANY);
	sst.sin_port = htons(static_cast<uint16_t>(port));

	g_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (g_fd < 0)
		return (std::cerr << "Error when trying to create a new socket " << std::endl, 1);
	int yes = 1;
	setsockopt(g_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
	bind_return = bind(g_fd, reinterpret_cast<sockaddr*>(&sst), sizeof(sst));
	if (bind_return < 0)
	{
		close(g_fd);
		return (std::cerr << "Error when trying to bind the socket " << std::endl, 1);
	}
	if (listen(g_fd, SOMAXCONN) < 0)
	{
		close(g_fd);
		return (std::cerr << "Error when trying to listen the socket " << std::endl, 1);
	}
	serv_loop();
	close(g_fd);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac == 3)
	{
		int port = parse_port(av[1]);
		if (port == -1)
		{
			std::cerr << "PORT MUST BE BETWEEN 1024 and 49151" << std::endl;
			return (1);
		}
		std::string password = parse_password(av[2]);
		if (password.empty())
		{
			print_password_protocol();
			return (1);
		}
		if (start_serv(port, password))
			return (1);
	}
}
