#include "Commande.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "IRC.hpp"

static std::vector<std::string> split(const std::string &str, char delim)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream stream(str);
	while (getline(stream, token, delim))
		tokens.push_back(token);
	return tokens;
}

int registredClient(std::vector<std::string> &parts, Client &client, std::string password, std::string command, std::vector<Client> &clients)
{
	if (command != "PASS" && client.getRegistredPassWord() == false)
		return (client.sendReply(ERR_NOTREGISTERED), 1);
	if (command == "PASS")
		if (!goToPass(password, parts, client))
			return 1;
	if (client.getRegistredPassWord() == false)
		return 1;
	if (command != "NICK" && command != "USER" && command != "PASS")
		return (client.sendReply("Error command"), 1);
	if (command == "NICK")
		if (!goToNickName(parts, client, clients))
			return 1;
	if (command == "USER")
		if (!goToUser(parts, client, clients))
			return 1;
	if (client.isReadyToRegister() && !client.isWelcomeSent())
	{
		client.sendReply(":serveur 001 " + client.getNickName() + " :Welcome to the IRC server, " + client.getNickName() + "!\r\n");
		client.setWelcomeSent(true);
	}
	return 0;
}

// Execute all commands
void executeCommand(std::string &line, Client &client, std::string password, std::vector<Channel> &channels, std::vector<Client> clients)
{
	std::cout << client << std::endl;
	std::vector<std::string> parts = split(line, ' ');
	std::string command = parts[0];
	if (!client.isReadyToRegister())
		if (!registredClient(parts, client, password, command, clients))
			return;
	if (command == "JOIN")
		if (!goToJoin(parts, client, channels, clients))
			return;
	if (command == "MODE")
		if (!goToMode(parts, client, channels, clients))
			return;
	return;
}
