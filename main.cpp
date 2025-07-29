/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:06:35 by skock             #+#    #+#             */
/*   Updated: 2025/07/29 16:31:33 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"


int	main(int ac, char **av)
{
	if (ac == 3)
	{
		int port = parse_port(av[1]);
		if (port == -1)
		{
			std::cout << "PORT MUST BE BETWEEN 1024 and 49151" << std::endl;
			return (1);
		}
		std::string password = parse_password(av[2]);
	}
	// int fd;
	// // int bind_return;
	// sockaddr_in	sst;
	// memset(&sst.sin_zero, 0, sizeof(sst.sin_zero));
	// sst.sin_family = AF_INET;
	// sst.sin_addr.s_addr = htonl(INADDR_ANY);
	// sst.sin_port = htons()

	// sst->sin_addr.s_addr = inet_addr(av[1]);
	// uint32_t addr = ntohl(sst->sin_addr.s_addr);

	// std::cout << addr << std::endl;
	// std::cout << static_cast<uint32_t>(sst->sin_addr.s_addr) << std::endl;
	

	// fd = socket(AF_INET, SOCK_STREAM, 0);
	// if (fd < 1)
	// 	std::cout << "Error when trying to create a new socket " << std::endl;
	// // bind_return = bind(fd, )
	// delete sst;
}
