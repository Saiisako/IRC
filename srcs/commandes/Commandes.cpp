#include "Commande.hpp"
#include "Client.hpp"

// Fonction Split
static std::vector<std::string> split(const std::string &str, char delim)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream stream(str);
	while (getline(stream, token, delim))
		tokens.push_back(token);
	return tokens;
}

// Execute all commands
bool executeCommand(std::string &line, client &client, std::string password)
{
	std::cout << password << std::endl;
	std::vector<std::string> parts = split(line, ' ');
	std::string command = parts[0];

	if (command == "NICK")
		if (goToNickName(parts, client) == false)
			return false;
	if (command == "USER")
		if (goToUser(parts, client) == false)
			return false;

	if (command == "JOIN")
		if (goToJoin(parts, client) == false)
			return false;

	return true;
}
