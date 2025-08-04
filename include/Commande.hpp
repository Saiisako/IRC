#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <cstring>
#include "Channel.hpp"

#define Vstring std::vector<std::string>

class Client;

//-------------------command config_clients-------------------------
void	executeCommand(std::string &line, Client &client, std::string password, std::vector<Channel> &channels);
void	goToNickName(std::vector<std::string> &parts, Client &client);
void	goToUser(std::vector<std::string> &parts, Client &client);
void	goToJoin(std::vector<std::string> parts, Client &client, std::vector<Channel> &channels);
void	privmsg(std::vector<std::string> &parts, std::vector<Channel> &channels, Client &clients);
Vstring	split(const std::string &str, char delim);