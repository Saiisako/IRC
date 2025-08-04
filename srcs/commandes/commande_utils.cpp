
#include "Commande.hpp"
#include "Client.hpp"
#include "IRC.hpp"

//'-' | '[' | ']' | '\' | '`' | '^' | '{' | '}'

bool special_char(char c)
{
	if (c == '-' || c == '[' || c == ']' || c == '\\' || c == '`' || c == '^' || c == '{' || c == '}')
		return true;
	return false;
}

// Parsing string name
bool isValidname(std::string &nick, Client &client)
{
	if (nick.empty())
		return false;

	if (!isalpha(nick[0]))
		return (client.sendReply("Error character Nick or user " + nick), false);
	for (unsigned i = 1; nick[i]; i++)
	{
		if (!isalpha(nick[i]) && !isalnum(nick[i]) && special_char(nick[i]) && nick[i] != '\n')
			return (client.sendReply("Error character Nick or user " + nick), false);
		if (i > 9)
			return (client.sendReply("Error lenght"), false);
	}
	return true;
}

std::vector<std::string> split(const std::string &str, char delim)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream stream(str);
	while (getline(stream, token, delim))
		tokens.push_back(token);
	return tokens;
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v)
{
	for (std::vector<std::string>::const_iterator it = v.begin(); it != v.end(); ++it)
		os << *it << std::endl;
	return os;
}