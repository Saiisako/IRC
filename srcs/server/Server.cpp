/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:26:45 by skock             #+#    #+#             */
/*   Updated: 2025/08/04 21:44:13 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Commande.hpp"
#include "Channel.hpp"

// CONSTRUCT/DESTRUCT
Server::Server(std::string password, std::string port) {}
Server::~Server() {}

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