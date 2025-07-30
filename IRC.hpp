/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skock <skock@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:07:49 by skock             #+#    #+#             */
/*   Updated: 2025/07/30 16:59:54 by skock            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <sys/socket.h>
# include <sys/types.h>
# include <errno.h>
# include <unistd.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <string.h>
# include <cstdlib>
# include <cctype>
# include <vector>
# include <sys/epoll.h> 

extern int g_fd;
// PARSING

int	parse_port(char *av);
std::string parse_password(char *av);

// UTILS

void	verify_password2(int length, int lower_count, int upper_count, int special_count, int digit_count, std::string &password);
void	verify_password1(std::string &password);
int		count_lowercase(std::string &password);
int		count_upper(std::string &password);
int		is_special_char(char c);
int		count_special(std::string &password);
void	print_password_protocol(void);
int		count_digit(std::string &password);
