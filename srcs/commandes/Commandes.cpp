#include "IRC.hpp"

int registredClient(std::vector<std::string> &parts, Client &client, std::string password, std::string command, std::vector<Client *> &clients)
{
	if (command != "PASS" && client.getRegistredPassWord() == false)
	{
		client.sendReply(ERR_UNKNOWNCOMMAND(command));
		return 1;
	}
	if (command == "PASS")
		if (!goToPass(password, parts, client))
			return 1;
	if (!client.getRegistredPassWord())
	{
		client.sendReply(ERR_NOTREGISTERED);
		return 1;
	}
	if (command != "NICK" && command != "USER" && command != "PASS")
	{
		client.sendReply(ERR_UNKNOWNCOMMAND(command));
		return 1;
	}
	if (command == "NICK")
		if (!goToNickName(parts, client, clients))
			return 1;
	if (command == "USER")
		if (!goToUser(parts, client))
			return 1;
	if (client.isReadyToRegister() && !client.isWelcomeSent())
	{
		client.sendReply(":serveur 001 " + client.getNickName() + " :Welcome to the IRC server, " + client.getNickName());
		client.setWelcomeSent(true);
	}
	return 0;
}

// Execute all commands
void executeCommand(std::string &line, Client &client, std::string password, std::vector<Channel *> &channels, std::vector<Client *> &clients)
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
	if (command == "PRIVMSG")
		if (!goToPrivMsg(parts, client, channels, clients))
			return;
	if (command == "INVITE")
		if (!goToInvite(parts, client, channels, clients))
			return;
	return;
}
