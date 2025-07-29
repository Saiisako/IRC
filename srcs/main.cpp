/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelecoq <jelecoq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:06:35 by skock             #+#    #+#             */
/*   Updated: 2025/07/29 18:53:21 by jelecoq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "IRC.hpp"

// int	main(int ac, char **av)
//{
//	(void)ac;
//	(void)av;
//	int fd;
//	// int bind_return;
//	sockaddr_in	*sst;

//	sst = new sockaddr_in;

//	sst->sin_addr.s_addr = inet_addr(av[1]);
//	uint32_t addr = ntohl(sst->sin_addr.s_addr);

//	std::cout << addr << std::endl;
//	std::cout << static_cast<uint32_t>(sst->sin_addr.s_addr) << std::endl;

//	fd = socket(AF_INET, SOCK_STREAM, 0);
//	if (fd < 1)
//		std::cout << "Error when trying to create a new socket " << std::endl;
//	// bind_return = bind(fd, )
//	delete sst;
//}

#include "Client.hpp"
#include "Commande.hpp"

int main(int argc, char **argv)
{
	if (argc == 1)
		return 1;
	client testClient(1);
	std::string input = argv[1];
	if (commande::executeCommand(input, &testClient) == false)
		return (1);

	std::cout << "Nickname actuel : " << testClient.getNickname() << std::endl;
	return 0;
}
