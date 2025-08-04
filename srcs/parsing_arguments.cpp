/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_arguments.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jelecoq <jelecoq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:28:30 by skock             #+#    #+#             */
/*   Updated: 2025/08/04 14:56:34 by jelecoq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"

int parse_port(char *av)
{
	int port = std::atoi(av);
	if (port <= 1024 || port >= 49151)
		port = -1;
	return (port);
}

std::string parse_password(char *av)
{
	int lower_count = 0, upper_count = 0, special_count = 0, digit_count = 0, length = 0;
	std::string password;
	password.assign(av);
	verify_password1(password);
	if (password.empty())
		return (password);
	length = password.size();
	lower_count = count_lowercase(password);
	upper_count = count_upper(password);
	digit_count = count_digit(password);
	special_count = count_special(password);
	verify_password2(length, lower_count, upper_count, special_count, digit_count, password);
	return (password);
}
