#ifndef COMMANDE_HPP
#define COMMANDE_HPP

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <cstring>

class client;

class commande
{
private:
	commande();
	~commande();

public:
	static bool executeCommand(std::string &line, client *client);
};

bool isValidNickname(std::string &nick);
bool goToNickName(std::vector<std::string> &parts, client *client);

#endif
