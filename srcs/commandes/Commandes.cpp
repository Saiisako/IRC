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
bool commande::executeCommand(std::string &line, client *client)
{
	if (client->getRegistred() == true)
		return (std::cerr << "Error USER already registred" << std::endl, false);

	std::vector<std::string> parts = split(line, ' ');
	if (parts.empty())
		return (std::cerr << "Error empty" << std::endl, false);

	std::string command = parts[0];
	if (command != "NICK" && command != "USER")
		return (std::cerr << "Error command" << std::endl, false);

	if (command == "NICK")
		if (goToNickName(parts, client) == false)
			return false;
	if (command == "USER")
		if (goToUser(parts, client) == false)
			return false;
	return true;
}
