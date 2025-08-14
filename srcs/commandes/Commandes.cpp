#include "IRC.hpp"

int registredClient(std::vector<std::string> &parts, Client &client, std::string &password, std::string &command, std::vector<Client *> &clients)
{
	if (command == "bp1")
	{
		client.setNickname("Saiisako", clients, client);
		client.setUserName("Sacha");
		client.setRealName("Salut !");
		client.setRegistredNick();
		client.setRegistredUser(true);
		client.setRegistredPassWord();
	}
	else if (command == "bp2")
	{
		client.setNickname("Jess", clients, client);
		client.setUserName("Jessica");
		client.setRealName("Bonjour");
		client.setRegistredNick();
		client.setRegistredUser(true);
		client.setRegistredPassWord();
	}
	else if (command == "bp3")
	{
		client.setNickname("LeBonSushi", clients, client);
		client.setUserName("Maxence");
		client.setRealName("Yolo");
		client.setRegistredNick();
		client.setRegistredUser(true);
		client.setRegistredPassWord();
	}
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
	if (command != "NICK" && command != "USER" && command != "PASS" && command != "bp1" && command != "bp2" && command != "bp3")
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

std::vector<std::string>	cut_to_string(std::vector<std::string> &parts, int flag)
{
	std::vector<std::string> new_part;

	for (std::vector<std::string>::iterator it = parts.begin() + 1; it != parts.end(); ++it)
		new_part.push_back(*it);

	std::string res;
	int i = 0;
	for (std::vector<std::string>::iterator it = new_part.begin() + flag; it != new_part.end(); ++it)
	{
		if (!i)
			res += *it;
		else
			res += " " + *it;
		i++;
	}

	new_part.erase(new_part.begin() + flag, new_part.end());
	new_part.push_back(res);

	return new_part;
}

// Execute all commands
void executeCommand(std::string &line, Client &client, std::string password, std::vector<Channel *> &channels, std::vector<Client *> &clients)
{
	std::cout << client << std::endl;
	std::vector<std::string> parts = split(line, ' ');
	std::string command = parts[0];
	if (!client.isReadyToRegister())
	{
		if (!registredClient(parts, client, password, command, clients))
			return;
	}
	if (command == "JOIN")
		if (!goToJoin(parts, client, channels, clients))
			return;
	if (command == "MODE")
		if (!goToMode(parts, client, channels, clients))
			return;
	if (command == "KICK")
	{
		if (parts.size() < 3)
		{
			client.sendReply(ERR_NEEDMOREPARAMS(client.getNickName()));
			return;
		}
		std::vector<std::string> arguments = cut_to_string(parts, 2);
		std::cout << arguments << std::endl;
		if (!goToKick(parts, client, channels, clients))
			return;
	}
	if (command == "PRIVMSG")
	{
		if (parts.size() < 3)
		{
			client.sendReply(ERR_NEEDMOREPARAMS(client.getNickName()));
			return;
		}
		std::vector<std::string> arguments = cut_to_string(parts, 1);
		if (!goToPrivMsg(arguments, client, channels, clients))
			return;
	}
	if (command == "INVITE")
		if (!goToInvite(parts, client, channels, clients))
			return;
	return;
}
