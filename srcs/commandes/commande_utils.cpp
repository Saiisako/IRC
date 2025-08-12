
#include "Commande.hpp"
#include "Client.hpp"
#include "IRC.hpp"

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &v)
{
	for (std::vector<std::string>::const_iterator it = v.begin(); it != v.end(); ++it)
		os << *it << std::endl;
	return os;
}

// #define ERR_NONICKNAMEGIVEN(nick) "431 " + nick + " :No nickname given\n"

//// Returned after receiving a NICK message which contains characters which do not fall in the defined set.
// #define ERR_ERRONEUSNICKNAME(nick) "432 " + nick + " :Erroneus nickname\n"

//// Returned when a NICK message is processed that results in an attempt to change to a currently existing nickname.
// #define ERR_NICKNAMEINUSE(nick) "433 " + nick + " :Nickname is already in use\n"
