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

// Execute all commands
bool executeCommand(std::string &line, Client &client, std::string password, std::vector<Channel> &channels)
{
	std::cout << client << std::endl;

	// if (verify_password(line, client, password))
	//	return (false);
	std::vector<std::string> parts = split(line, ' ');
	std::string command = parts[0];
	if (command != "PASS" && client.getRegistredPassWord() == false)
	{
		client.sendReply(":server 464 * :Password required\r\n");
		return false;
		// close serveur ;
	}
	if (command == "PASS")
		return (goToPass(password, parts, client) == false);
	if (client.getRegistredPassWord() == false)
		return false;
	if (command != "NICK" && command != "USER" && command != "JOIN")
		return (client.sendReply("Error command"), false);
	if (command == "NICK")
		if (goToNickName(parts, client) == false)
			return false;
	if (command == "USER")
		if (goToUser(parts, client) == false)
			return false;
	if (command == "JOIN")
		if (goToJoin(parts, client, channels) == false)
			return false;
	if (client.isReadyToRegister() && !client.isWelcomeSent())
	{
		client.sendReply(":serveur 001 " + client.getNickName() + " :Bienvenue sur le serveur IRC, " + client.getNickName() + "!\r\n");
		client.setWelcomeSent(true);
	}
	return true;
}
