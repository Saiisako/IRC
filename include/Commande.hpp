#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <cstring>
#include "Channel.hpp"
#include "Client.hpp"

//-------------------command config_clients-------------------------
bool executeCommand(std::string &line, Client &client, std::string password, std::vector<Channel> &channels);

bool goToPass(std::string &password, std::vector<std::string> &parts, Client &client);
bool goToNickName(std::vector<std::string> &parts, Client &client);
bool goToUser(std::vector<std::string> &parts, Client &client);
bool goToJoin(std::vector<std::string> parts, Client &client, std::vector<Channel> &channels);
