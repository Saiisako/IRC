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

// Execute commands
bool commande::executeCommand(std::string &line, client *client)
{
	std::vector<std::string> parts = split(line, ' ');
	if (parts.empty())
	{
		std::cerr << "Error empty" << std::endl;
		return false;
	}
	std::string command = parts[0];

	if (command != "NICK")
	{
		std::cerr << "Error command" << std::endl;
		return false;
	}
	if (command == "NICK")
		if (goToNickName(parts, client) == false)
			return false;
	return true;
}
