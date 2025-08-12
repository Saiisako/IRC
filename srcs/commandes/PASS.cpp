

#include "IRC.hpp"

bool goToPass(std::string &password, std::vector<std::string> &parts, Client &client)
{
	if (client.isReadyToRegister() == true)
		return (client.sendReply(ERR_ALREADYREGISTRED), false);
	if (parts.size() < 2)
		return (client.sendReply(ERR_NEEDMOREPARAMS(parts[0])), false);
	std::string passwordClient = parts[1];
	if (password != passwordClient)
		return (client.sendReply(ERR_PASSWDMISMATCH), false);
	client.setRegistredPassWord();
	return true;
}
