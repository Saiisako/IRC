/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/08/11 10:02:34 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <sys/epoll.h>
#include "Channel.hpp"
#include "Error.hpp"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

extern int g_password;
// PARSING

int parse_port(char *av);

// UTILS

bool		isValidname(std::string &nick, Client &client);
std::string	join_buffer(const std::string& buffer);
std::vector<std::string> split(const std::string &str, char delim);

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v);