#pragma once

#include <vector>
#include <string>

#define USAGE "./ircserv [port] [password]"
#define BOT_USAGE "./turco [port] [password]"
#define VECT_STR std::vector<std::string>
#define VECT_ITER_CLI std::vector<Client>::iterator
#define VECT_ITER_CONST_CLI std::vector<Client>::const_iterator
#define VECT_CLI std::vector<Client>
#define C_VECT_CLI_R const std::vector<Client>&
#define VECT_ITER_CHA std::vector<Room>::iterator

#define C_VECT_STR const std::vector<std::string>
#define C_VECT_STR_R C_VECT_STR&
#define C_STR const std::string
#define C_STR_REF const std::string &

#define INV_PARAM "Invalid parameters\n"

#define hexchat 1
#define bot_cap 2

#define KEY_CODE 1
#define LIMIT_CODE 2


// HEXCHAT COMMANDS (RFC 1459)
# define JOIN_RESPONSE(nick, ip, channel) ":" + nick + "!" + nick + "@" + ip + " JOIN " + channel + "\r\n"
# define RPL_TOPIC_JOIN(nick, ip, channel, topic) ":" + nick + "!" + nick + "@" + ip + " TOPIC " + channel + " :" + topic + "\r\n"
# define RPL_KICK(source, channel, target, reason)	":" + source + " KICK " + channel + " " + target + " :" + reason + "\r\n"
# define RPL_NICK(nick, user, ip, newnick) ":" + nick + "!" + user + "@" + ip + " NICK :" + newnick + "\r\n"
# define RPL_PART(source, channel, reason)	":" + source + " PART " + channel + " :" + reason + "\r\n"
# define RPL_PING(source, nick, second)				":" + source + " PONG " + nick + " :"+ second + "\r\n"
# define MSG_GROUP(nick,user, host, room, message) ":" + nick + "!" + user + "@" + host + " PRIVMSG  " + room + " :" + message + "\r\n"
# define RPL_NOTICE(source, target, message) ":" + source + " NOTICE " + target + " :" + message + "\r\n"
# define RPL_PRIVMSG(source, target, message)		":" + source + " PRIVMSG " + target + " :" + message + "\r\n"
#define RPL_QUIT(source, message)                   ":" + source + " QUIT :" + message + "\r\n"
#define RPL_TOPICSET(nick, channel, operator, time) ": 333 " + nick + " " + channel + " " + operator + " " + time + "\r\n"

# define ERR_OWNKICK(source, channel) ": 443 " + source + " " + channel + " :You can't kick yourself" + "\r\n"
