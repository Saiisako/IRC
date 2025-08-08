/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:28:30 by skock             #+#    #+#             */
/*   Updated: 2025/08/08 14:59:05 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

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
