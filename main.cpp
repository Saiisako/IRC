/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:06:35 by skock             #+#    #+#             */
/*   Updated: 2025/07/29 13:24:09 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	int fd;
	// int bind_return;
	sockaddr_in	*sst;

	sst = new sockaddr_in;

	sst->sin_addr.s_addr = inet_addr(av[1]);
	uint32_t addr = ntohl(sst->sin_addr.s_addr);

	std::cout << addr << std::endl;
	std::cout << static_cast<uint32_t>(sst->sin_addr.s_addr) << std::endl;
	

	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd < 1)
		std::cout << "Error when trying to create a new socket " << std::endl;
	// bind_return = bind(fd, )
	delete sst;
}