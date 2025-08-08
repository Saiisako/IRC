/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   password_utils.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:27:03 by skock             #+#    #+#             */
/*   Updated: 2025/08/08 18:16:51 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"
#include "Client.hpp"
#include "Commande.hpp"
#include "Channel.hpp"

int	parse_port(char *av)
{
	int port = std::atoi(av);
	if (port <= 1024 || port >= 49151)
		port = -1;
	if (port == -1)
	{
		std::cerr << "PORT MUST BE BETWEEN 1024 and 49151" << std::endl;
		exit(1);
	}
	return (port);
}

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

std::vector<std::string> split(const std::string &str, char delim)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream stream(str);
	while (getline(stream, token, delim))
		tokens.push_back(token);
	return tokens;
}
