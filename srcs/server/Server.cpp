/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:26:45 by skock             #+#    #+#             */
/*   Updated: 2025/08/08 15:50:17 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Commande.hpp"
#include "Channel.hpp"

// CONSTRUCT/DESTRUCT
Server::Server(std::string password, std::string port)
{
	this->_password = password;
	this->_servPort = std::atoi(port.c_str());
}
Server::~Server() {}

// SERVER RUNNER
void Server::boot()
{
	sockaddr_in sst;
	memset(&sst.sin_zero, 0, sizeof(sst.sin_zero));
	sst.sin_family = AF_INET;
	sst.sin_addr.s_addr = htonl(INADDR_ANY);
	sst.sin_port = htons(static_cast<uint16_t>(_servPort));
	
	_socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_socketFd < 0)
	{
		std::cerr << "Error when trying to create a new socket " << std::endl;
		exit(1);
	}
	int set_socket = 1;
	setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &set_socket, sizeof set_socket);
	if (bind(_socketFd, (sockaddr*)&sst, sizeof(sst)) < 0)
	{
		close(_socketFd);
		std::cerr << "Error when trying to bind the socket " << std::endl;
		exit(1);
	}
	if (listen(_socketFd, SOMAXCONN) < 0)
	{
		close(_socketFd);
		std::cerr << "Error when trying to listen the socket " << std::endl;
		exit(1);
	}
	return ;
}

void Server::run()
{
	while (1)
	{
		fd_set readfds;
		FD_ZERO(&readfds);
		FD_SET(_socketFd, &readfds);
		int max_fd = _socketFd;
		for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it)
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
		if (FD_ISSET(_socketFd, &readfds))
		{
			sockaddr_in client_addr;
			socklen_t addrlen = sizeof(client_addr);
			int client_fd = accept(_socketFd, reinterpret_cast<sockaddr*>(&client_addr), &addrlen);
			std::cout << client_fd << std::endl;
			Client cli(client_fd);
			if (client_fd >= 0)
			{
				clients.push_back(cli);
				std::cout << "New client connected: fd " << client_fd << std::endl;
			}
		}
		for (std::vector<Client>::iterator it = clients.begin(); it != clients.end();)
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
				if (!new_str.empty())
					executeCommand(new_str, *it, _password, channels, clients);
				else
					send(client_fd, "line empty\n", 11, 0);
			}
			++it;
		}
	}
}

// GET
int Server::getSocketFd() { return (_socketFd); }
int	Server::getServPort() { return (_servPort); }
std::string Server::getPassword() { return (_password); }
std::string Server::getServName() { return (_servName); }
// SET
void	Server::setSocketFd(int fd) { _socketFd = fd; }
void	Server::setServPort(int port) { _servPort = port; }
void	Server::setPassword(std::string password) { _password = password; }
void	Server::setServName(std::string serverName) { _servName = serverName; }