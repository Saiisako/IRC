#include "Commande.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "../../include/IRC.hpp"

int	verify_password(std::string &line, Client &client, std::string password)
{
	if (client.getRegistredPassWord() == true)
		return 0;
	else if (line == password)
	{
		send(client.getFd(), "\033[32mCorrect Password\n\033[0m", 26, 0);
		client.setRegistredPassWord();
	}
	else
		send(client.getFd(), "\033[31mIncorrect Password\n\033[0m", 28, 0);
	return (1);
}

bool	is_registered(Client &client)
{
	if (client.getRegistredNick() == true && client.getRegistredPassWord() == true && client.getRegistredUser() == true)
		return true;
	return false;
}
// Execute all commands
void executeCommand(std::string &line, Client &client, std::string password, std::vector<Channel> &channels)
{
	std::cout << client << std::endl;
	if (verify_password(line, client, password))
		return ;
	std::vector<std::string> parts = split(line, ' ');
	if (line == "\r\n")
		return (client.sendReply("Error empty"));
	std::string command = parts[0];
	if (command != "NICK" && command != "USER" && command != "JOIN" && command != "PRIVMSG")
		return (client.sendReply("Error command"));
	else if (command == "NICK")
		return goToNickName(parts, client);
	else if (command == "USER")
		return goToUser(parts, client);
	else if (command == "JOIN")
		return goToJoin(parts, client, channels);
	if (is_registered(client))
	{
		if (command == "PRIVMSG")
			return (privmsg(parts, channels, client));
	}
	else
		return (client.sendReply("You are not finished registering\n"));
}
