/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:27:03 by skock             #+#    #+#             */
/*   Updated: 2025/07/29 16:31:26 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRC.hpp"


void	verify_password2(int length, int lower_count, int upper_count, int special_count, int digit_count, std::string &password)
{
	if (!lower_count)
		password.assign(NULL);
	if (!upper_count)
		password.assign(NULL);
	if (!special_count)
		password.assign(NULL);
	if (!digit_count)
		password.assign(NULL);
}

int	count_lowercase(std::string &password)
{
	int lowercase_count = 0;
	for (size_t i = 0; password[i] ; i++)
	{
		if (islower(password[i]))
			lowercase_count++;
	}
	return (lowercase_count);
}

int	count_upper(std::string &password)
{
	int upper_count = 0;
	for (size_t i = 0; password[i] ; i++)
	{
		if (std::isupper(password[i]))
			upper_count++;
	}
	return (upper_count);
}

int	is_special_char(char c)
{
	if (c == '!' || c == '\'' || c == '-' || c == '_' ||
		c == '{' || c == '}'  || c == '[' || c == ']' ||
		c == '(' || c == ')'  || c == '@' || c == '$' ||
		c == '?' || c == ';'  || c == ':')
		return 1;
	else
		return 0;
}

int	count_special(std::string &password)
{
	int special_count = 0;
	for (size_t i = 0; password[i] ; i++)
	{
		if (is_special_char(password[i]))
			special_count++;
	}
	return (special_count);
}

int	count_digit(std::string &password)
{
	int digit_count = 0;

	for (size_t i = 0; password[i] ; i++)
	{
		if (std::isdigit(password[i]))
			digit_count++;
	}
	return (digit_count);
}

void verify_password1(std::string &password)
{
	bool invalid_char_found = false;

	for (size_t i = 0; i < password.length() && !invalid_char_found; i++)
	{
		if (!(is_special_char(password[i]) || isupper(password[i]) ||
			islower(password[i]) || isdigit(password[i])))
			invalid_char_found = true;
	}
	if (invalid_char_found)
		password.assign(NULL);
}
