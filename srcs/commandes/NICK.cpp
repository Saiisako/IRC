
#include "Commande.hpp"
#include "Client.hpp"
#include "IRC.hpp"

// Execute command : NICK <nickname> -> change the client nickname after the client is set
void goToNickName(std::vector<std::string> &parts, Client &client)
{
	static bool flag = false;
	if (parts.size() < 2)
		return (client.sendReply("Error arguments NICK"));
	std::string nickname = parts[1];
	if (isValidname(nickname, client) == false)
		return ;
	if (client.getRegistredUser() == false)
		client.sendReply("Add User for valid the all profil client");
	else if (flag == false && client.getRegistredUser() == true)
	{
		client.sendReply("Your profil is create");
		flag = true;
	}
	else if (client.getRegistredNick() == true)
		client.sendReply("Your nickname has been changed");
	client.setNickname(nickname);
	client.setRegistredNick();
}
