#include "Commande.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "IRC.hpp"

int verify_password(std::string &line, Client &client, std::string password)
{
	if (client.getRegistredPassWord() == true)
	{
		std::cout << "here0" << std::endl;
		return 0;
	}
	else if (line == password)
	{
		send(client.getFd(), "\033[32mCorrect Password\n\033[0m", 26, 0);
		client.setRegistredPassWord();
	}
	else
		send(client.getFd(), "\033[31mIncorrect Password\n\033[0m", 28, 0);
	return (1);
}

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

int registredClient(std::vector<std::string> &parts, Client &client, std::string password, std::string command)
{

	if (command != "PASS" && client.getRegistredPassWord() == false)
		return (client.sendReply(":server 464 * :Password required\r\n"), 1);
	if (command == "PASS")
		if (!goToPass(password, parts, client))
			return 1;
	if (client.getRegistredPassWord() == false)
		return 1;
	if (command != "NICK" && command != "USER" && command != "PASS")
		return (client.sendReply("Error command"), 1);
	if (command == "NICK")
		if (!goToNickName(parts, client))
			return 1;
	if (command == "USER")
		if (!goToUser(parts, client))
			return 1;
	if (client.isReadyToRegister() && !client.isWelcomeSent())
	{
		client.sendReply(":serveur 001 " + client.getNickName() + " :Welcome to the IRC server, " + client.getNickName() + "!\r\n");
		client.setWelcomeSent(true);
	}
	return 0;
}

// Execute all commands
void executeCommand(std::string &line, Client &client, std::string password, std::vector<Channel> &channels)
{
	std::cout << client << std::endl;
	std::vector<std::string> parts = split(line, ' ');
	std::string command = parts[0];
	if (!client.isReadyToRegister())
		if (!registredClient(parts, client, password, command))
			return;
	std::cout << "CLIENT NICKNAME IN EXEC = [" << client.getNickName() << "]" << std::endl;
	if (command == "JOIN")
		if (goToJoin(parts, client, channels) == false)
			return;
	return;
}
