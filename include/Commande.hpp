#ifndef COMMANDE_HPP
#define COMMANDE_HPP

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <cstring>
#include "Client.hpp"

//-------------------command config_clients-------------------------
bool executeCommand(std::string &line, client &client, std::string password);
bool goToNickName(std::vector<std::string> &parts, client &client);
bool goToUser(std::vector<std::string> &parts, client &client);
bool goToJoin(std::vector<std::string> parts, client &client);

#endif
