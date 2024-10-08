#include "Client.hpp"

#include "Exception.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Room.hpp"
#include "Utils.hpp"
#include "TextEngine.hpp"
#include "Define.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

/*
	4.2.8 Kick command

	Command: KICK
	Parameters: <channel> <user> [<comment>]

	The KICK command can be  used  to  forcibly  remove  a  user  from  a
	channel.   It  'kicks  them  out'  of the channel (forced PART).

	Only a channel operator may kick another user out of a  channel.
	Each  server that  receives  a KICK message checks that it is valid
	(ie the sender is actually a  channel  operator)  before  removing
	the  victim  from  the channel.

	Numeric Replies:

	        ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
	        ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
	        ERR_NOTONCHANNEL

	Examples:

	KICK &Melbourne Matthew         ; Kick Matthew from &Melbourne

	KICK #Finnish John :Speaking English
	                                ; Kick John from #Finnish using
	                                "Speaking English" as the reason
	                                (comment).

	:WiZ KICK #Finnish John         ; KICK message from WiZ to remove John
	                                from channel #Finnish

	NOTE:
	     It is possible to extend the KICK command parameters to the
	following:

	<channel>{,<channel>} <user>{,<user>} [<comment>]

*/

void Server::kick(C_STR_REF input, Client &fd)
{
	if (fd.getIsRegistered() == false)
	{
		Utils::instaWrite(fd.getFd(), ERR_NOTREGISTERED(fd.getNick()));
		return;
	}
	VECT_STR splited = Utils::ft_split(input, " ");
	string nick, channel, message;
	if (splited.size() < 2)
	{
		Utils::instaWrite(fd.getFd(), ERR_NEEDMOREPARAMS(fd.getNick(), "KICK"));
		return;
	}
	channel = splited[0];
	nick = splited[1];
	if (splited.size() == 2)
	{
		message = "Kicked";
	}
	else 
		message = Utils::ft_join(splited, " ", 2);
	if (message[0] == ':')
	{
		message = message.substr(1);
	}
	if (channel[0] != '#')
	{
		channel = "#" + channel;
	}
	if (!isRoom(channel))
	{	
		Utils::instaWrite(fd.getFd(), ERR_NOSUCHCHANNEL(fd.getNick(), channel));
		return;
	}
	Room &room = getRoom(channel);
	if (!room.isClientInChannel(fd.getFd()))
	{
		Utils::instaWrite(fd.getFd(), ERR_NOTONCHANNEL(fd.getNick(), channel));
		return;
	}
	if (!room.isClientInChannel(nick))
	{
		Utils::instaWrite(fd.getFd(), ERR_NOSUCHNICK(fd.getNick(), nick));
		return;
	}
	if (!room.isOperator(fd))
	{
		Utils::instaWrite(fd.getFd(), ERR_CHANOPRIVSNEEDED(fd.getNick(), channel));
		return;
	}
	if (nick == fd.getNick())
	{
		Utils::instaWrite(fd.getFd(), ERR_OWNKICK(fd.getNick(), channel));
		return;
	}
	Client &kicked = getClientByNick(nick);
	room.removeClient(kicked.getFd());
	if (room.isOperator(kicked))
	{
		room.removeOperator(kicked);
	}
	Utils::instaWrite(kicked.getFd(), RPL_KICK(fd.getNick(), channel, kicked.getNick(), message));
	Utils::instaWriteAll(room.getClients(), RPL_KICK(fd.getNick(), channel, kicked.getNick(), message));
	responseAllClientResponseToGui(fd, room);
	TextEngine::red("Kicked " + nick + " from " + channel, TextEngine::printTime(std::cout)) << std::endl;
}
