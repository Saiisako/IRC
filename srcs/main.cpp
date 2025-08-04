/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:06:35 by skock             #+#    #+#             */
/*   Updated: 2025/08/04 13:09:53 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"
#include "../include/Commande.hpp"
#include "../include/Channel.hpp"
#include "../IRC.hpp"

int		g_fd;

std::string join_buffer(const std::string& buffer)
{
	static std::string accumulated;
	accumulated += buffer;

	size_t pos = accumulated.find('\n');
	if (pos != std::string::npos) {
		std::string result = accumulated.substr(0, pos);
		accumulated.erase(0, pos + 1);
		return result;
	}
	return ("");
}


void serv_loop(std::string password)
{
	std::vector<client> clients;
	while (1)
	{
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(g_fd, &readfds);
		int max_fd = g_fd;
		for (std::vector<client>::iterator it = clients.begin(); it != clients.end(); ++it)
		{
			FD_SET(it->getFd(), &readfds);
			if (it->getFd() > max_fd)
				max_fd = it->getFd();
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
			std::cout << client_fd << std::endl;
			client cli(client_fd);
			if (client_fd >= 0)
			{
				clients.push_back(cli);
				std::cout << "New client connected: fd " << client_fd << std::endl;
				send(client_fd, "Enter password to connect to serv\n", 34, 0);
			}
		}
		for (std::vector<client>::iterator it = clients.begin(); it != clients.end();)
		{
			int client_fd = it->getFd();
			if (FD_ISSET(client_fd, &readfds))
			{
				char buffer[1024];
				ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
				if (bytes <= 0)
				{
					close(client_fd);
					it = clients.erase(it);
					std::cout << "Client disconnected: fd " << client_fd << std::endl;
					continue;
				}
				buffer[bytes] = '\0';
				std::string new_str = join_buffer(buffer);

				std::cout << "Client FD: " << it->getFd() << std::endl;
				if (!new_str.empty())
				{
					std::cout << "[DBG]" << std::endl;
					executeCommand(new_str, *it, password);
				}
				send(it->getFd(), buffer, bytes, 0);
			}
			++it;
		}
	}
}

int start_serv(int port, std::string password)
{
	sockaddr_in sst;
	memset(&sst.sin_zero, 0, sizeof(sst.sin_zero));
	sst.sin_family = AF_INET;
	sst.sin_addr.s_addr = htonl(INADDR_ANY);
	sst.sin_port = htons(static_cast<uint16_t>(port));

	g_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (g_fd < 0)
		return (std::cerr << "Error when trying to create a new socket " << std::endl, 1);
	int yes = 1;
	setsockopt(g_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
	if (bind(g_fd, (sockaddr*)&sst, sizeof(sst)) < 0)
		return (close(g_fd), std::cerr << "Error when trying to bind the socket " << std::endl, 1);
	if (listen(g_fd, SOMAXCONN) < 0)
		return (close(g_fd), std::cerr << "Error when trying to listen the socket " << std::endl, 1);
	serv_loop(password);
	close(g_fd);
	return (1);
}

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	int port = parse_port(av[1]);
	if (port == -1)
	{
		std::cerr << "PORT MUST BE BETWEEN 1024 and 49151" << std::endl;
		return (1);
	}
	std::string password = parse_password(av[2]);
	return start_serv(port, password);
}
