/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 19:22:03 by skock             #+#    #+#             */
/*   Updated: 2025/08/04 19:30:07 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <iostream>

class Server
{
	private:
		std::string _socketFd;
		std::string _password;
		std::string _servName;
		std::string	_servPort;
	public:
		Server();
		~Server();
};
