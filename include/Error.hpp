
#pragma once

// ========================================================================== //
//   NICK                                                                     //
// ========================================================================== //

// Returned when a nickname parameter expected for a command and isn't found.
#define ERR_NONICKNAMEGIVEN(nick) "431 " + nick + " :No nickname given"

// Returned after receiving a NICK message which contains characters which do not fall in the defined set.
#define ERR_ERRONEUSNICKNAME(nick) "432 " + nick + " :Erroneus nickname"

// Returned when a NICK message is processed that results in an attempt to change to a currently existing nickname.
#define ERR_NICKNAMEINUSE(nick) "433 " + nick + " :Nickname is already in use"

// ========================================================================== //
//   PASS                                                                     //
// ========================================================================== //

// Returned by the server to indicate that the client must be registered before the server will allow it to be parsed in detail.
#define ERR_NOTREGISTERED "451 :You have not registered"

// Returned by the server to any link which tries to change part of the registered details.
#define ERR_ALREADYREGISTRED "462 :You may not reregister"

// Returned to indicate a failed attempt at registering a connection for which a password was required and was either not given or incorrect.
#define ERR_PASSWDMISMATCH "464 :Password incorrect"

#define ERR_UNKNOWNCOMMAND(command) "421 " + command + " :Unknown command"

// ========================================================================== //
//   Miscellaneous                                                            //
// ========================================================================== //

// Returned by the server by numerous commands to indicate to the client that it didn't supply enough parameters.
#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters"

// ========================================================================== //
//   JOIN                                                                     //
// ========================================================================== //

#define ERR_BADCHANNAME(nick, channel) "479 " + nick + " " + channel + " :Illegal channel name"
#define ERR_BADCHANNELKEY(channel) "475 " + channel + " :Cannot join channel (+k)"
#define ERR_INVITEONLYCHAN(channel) "473 " + channel + " :Cannot join channel (+i)"
#define ERR_CHANNELISFULL(channel) "471 " + channel + " :Cannot join channel (+l)"

// ========================================================================== //
//   PRIVMSG                                                                  //
// ========================================================================== //

// Returned by the server when there is no message to be send or incorrect format.
#define ERR_NOTEXTTOSEND(receiver) "412 " + receiver + " PRIVMSG" + " :No text to send"

// Returned by the server when there is no recipient to message.
#define ERR_NORECIPIENT(receiver) "411" + receiver + " PRIVMSG" + " :No recipient given"

/////////////////////////////////////////////////////////////////////////////////
#define ERR_BADCHANNELKEY(channel) "475 " + channel + " :Cannot join channel (+k)"
#define ERR_CHANNELISFULL(channel) "471 " + channel + " :Cannot join channel (+l)"
#define ERR_INVITEONLYCHAN(channel) "473 " + channel + " :Cannot join channel (+i)"
#define ERR_BANNEDFROMCHAN(channel) "474 " + channel + " :Cannot join channel (+b)"
// #define ERR_NOSUCHCHANNEL(server, user, channel) ":" + server + " 403 " + user + " " + channel + " :No such channel\r\n"
#define ERR_TOOMANYCHANNELS(channel) "405 " + channel + " :You have joined too many channels\n"
#define ERR_TOOMANYTARGETS(target, errorCode, abortMessage) "407 " + target + " :" + errorCode + "Too many recipients. " + abortMessage
#define ERR_UNAVAILRESOURCE(nick, channel) "437 " + nick + " " + channel + " :Nick/channel is temporarily unavailable"
#define ERR_BADCHANMASK(channel) "476 " + channel + " :Bad Channel Mask\n"

// ========================================================================== //
//   MODE                                                                     //
// ========================================================================== //

#define ERR_CHANOPRIVSNEEDED(nick) "482 " + nick + " :You're not a channel operator"
#define ERR_UNKNOWNMODE(modechar) "472 " + modechar + " :is unknown mode char to me"
#define ERR_INVALIDLIMIT(channel) "472 " + channel + " :Invalid channel limit"

// ========================================================================== //
//   INVITE                                                                     //
// ========================================================================== //

#define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel"
#define RPL_INVITING(nick, channel) "341 " + nick + " " + channel
