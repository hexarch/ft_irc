#include "Client.hpp"
#include "Server.hpp"
#include "Room.hpp"

#include "Exception.hpp"
#include "Utils.hpp"
#include "Define.hpp"

#include "Define.hpp"
#include <iostream>
#include <string>

#include <vector>
#include <cstdlib>



/*
	4.2.3 Mode message

	Command: MODE

	The MODE command is a dual-purpose command in IRC.  It allows both
	usernames and channels to have their mode changed.  The rationale for
	this choice is that one day nicknames will be obsolete and the
	equivalent property will be the channel.

	When parsing MODE messages, it is recommended that the entire message
	be parsed first and then the changes which resulted then passed on.

	4.2.3.1 Channel modes

	Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]
	            [<ban mask>]

	The MODE command is provided so that channel operators may change the
	characteristics of `their' channel.  It is also required that servers
	be able to change channel modes so that channel operators may be
	created.

	The various modes available for channels are as follows:

	        o - give/take channel operator privileges; (yapak)
	        i - invite-only channel flag; (yapak)
	        t - topic settable by channel operator only flag; (yapak)
	        n - no messages to channel from clients on the outside; (yapak)
	        l - set the user limit to channel; (yapak)
	        k - set a channel key (password). (yapak)
	        p - private channel flag;
	        s - secret channel flag;
	        m - moderated channel;
	        b - set a ban mask to keep users out;
	        v - give/take the ability to speak on a moderated channel;

	When using the 'o' and 'b' options, a restriction on a total of three
	per mode command has been imposed.  That is, any combination of 'o'
	and

	.3.2 User modes (only channel modes we want to do)

	Parameters: <nickname> {[+|-]|i|w|s|o}

	The user MODEs are typically changes which affect either how the
	client is seen by others or what 'extra' messages the client is sent.
	A user MODE command may only be accepted if both the sender of the
	message and the nickname given as a parameter are both the same.

	The available modes are as follows:

	        i - marks a users as invisible;
	        s - marks a user for receipt of server notices;
	        w - user receives wallops;
	        o - operator flag.

	Additional modes may be available later on.

	If a user attempts to make themselves an operator using the "+o"
	flag, the attempt should be ignored.  There is no restriction,
	however, on anyone `deopping' themselves (using "-o").  Numeric
	Replies:

	        ERR_NEEDMOREPARAMS (done)             RPL_CHANNELMODEIS
	        ERR_CHANOPRIVSNEEDED (done)           ERR_NOSUCHNICK
	        ERR_NOTONCHANNEL (done)               ERR_KEYSET
	        RPL_BANLIST                     RPL_ENDOFBANLIST
	        ERR_UNKNOWNMODE (done)                ERR_NOSUCHCHANNEL (done)

	        ERR_USERSDONTMATCH              RPL_UMODEIS
	        ERR_UMODEUNKNOWNFLAG

	Use of Channel Modes:

	MODE #Finnish +im           ; Makes #Finnish channel moderated and
	                            'invite-only'.

	MODE #Finnish +o Kilroy     ; Gives 'chanop' privileges to Kilroy on
	                            channel #Finnish.

	MODE #Finnish +v Wiz        ; Allow WiZ to speak on #Finnish.

	MODE #Fins -s               ; Removes 'secret' flag from channel
	                            #Fins.

	MODE #42 +k oulu            ; Set the channel key to "oulu".

	MODE #eu-opers +l 10        ; Set the limit for the number of users
	                            on channel to 10.

	MODE &oulu +b               ; list ban masks set for channel.

	MODE &oulu +b *!*@*         ; prevent all users from joining.

	MODE &oulu +b *!*@*.edu     ; prevent any user from a hostname
	                            matching *.edu from joining.
*/

namespace {
	string calcMode(const Room &room){
		string mode = "+";
		string modeValue = "";
		if (room.getKeycode() & FLAG_INV)
			mode += "i";
		if (room.getKeycode() & FLAG_TOPIC)
			mode += "t";
		if (room.getKeycode() & FLAG_NOOUTSIDE)
			mode += "n";
		if (room.getKeycode() & FLAG_LIMIT){
			mode += "l";
			modeValue = Utils::ft_itoa(room.getChanelLimit());
		}
		if (room.getKeycode() & FLAG_KEY){
			mode += "k";
			modeValue = (modeValue.empty() ? room.getKey() : modeValue + " " + room.getKey());
		}
		if (modeValue.empty())
			return mode;
		return mode + " " + modeValue;
	}
}

void Server::modeChannel(VECT_STR &params, Client &client)
{
	if (isRoom(params[0]) == false){
		Utils::instaWrite(client.getFd(), ERR_NOSUCHCHANNEL(client.getUserByHexChat(), params[0]));
		return;
	}
	Room &room = getRoom(params[0]);
	if (params.size() == 1){
		client.getmesagesFromServer().push_back(RPL_CHANNELMODEIS(client.getUserByHexChat(), params[0], calcMode(room)));
		FD_SET(client.getFd(), &writefds);
		return;
	}
	if (isClientInRoom(room, client) == false){
		Utils::instaWrite(client.getFd(), ERR_NOTONCHANNEL(client.getUserByHexChat(), params[0]));
		return;
	}
	if (room.isOperator(client) == false){
		Utils::instaWrite(client.getFd(), ERR_CHANOPRIVSNEEDED(client.getUserByHexChat(), params[0]));
		return;
	}
	if (params.size() > 3)
	{
		Utils::instaWrite(client.getFd(), ERR_UNKNOWNMODE(client.getUserByHexChat(), params[1]));
		return;
	}
	if (params[1][0] == '+'){
		for (size_t i = 1; i < params[1].size(); i++)
		{
			if (params[1][i] == 'o')
			{
				if (params.size() == 2)
				{
					Utils::instaWrite(client.getFd(), ERR_NEEDMOREPARAMS(client.getUserByHexChat(), "MODE"));
					return;
				}
				if (isClientInRoom(room, params[2]) == false)
				{
					Utils::instaWrite(client.getFd(), ERR_NOSUCHNICK(client.getUserByHexChat(), params[2]));
					return;
				}
				if (room.isOperator(params[2]) == true)
				{
					Utils::instaWrite(client.getFd(), ERR_ALREADYOPERATOR(client.getNick(), room.getName()));
					return;
				}
				Client &cli = getClientByNick(params[2]);
				room.addOperator(cli);
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "+" + params[1][i], params[2]));
			}
			else if (params[1][i] == 'i')
			{
				room.setKeycode(room.getKeycode() | FLAG_INV);
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "+" + params[1][i], ""));
			}
			else if (params[1][i] == 't')
			{
				room.setKeycode(room.getKeycode() | FLAG_TOPIC);
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "+" + params[1][i], ""));
			}
			else if (params[1][i] == 'n')
			{
				room.setKeycode(room.getKeycode() | FLAG_NOOUTSIDE);
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "+" + params[1][i], ""));
			}
			else if (params[1][i] == 'l')
			{
				if (params.size() == 2)
				{
					Utils::instaWrite(client.getFd(), ERR_NEEDMOREPARAMS(client.getUserByHexChat(), "MODE"));
					return;
				}
				else if (atoi(params[2].c_str()) < 0 || atoi(params[2].c_str()) < static_cast<int>(room.getClients().size()))
				{
					Utils::instaWrite(client.getFd(), ERR_BADLIMIT(client.getUserByHexChat(), params[2]));
					return;
				}
				room.setKeycode(room.getKeycode() | FLAG_LIMIT);
				room.setChanelLimit(atoi(params[2].c_str()));
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "+" + params[1][i], params[2]));
			}
			else if (params[1][i] == 'k')
			{
				if (params.size() == 2)
				{
					Utils::instaWrite(client.getFd(), ERR_NEEDMOREPARAMS(client.getUserByHexChat(), "MODE"));
					return;
				}
				room.setKeycode(room.getKeycode() | FLAG_KEY);
				room.setKey(params[2]);
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "+" + params[1][i], params[2]));
			}
			else
			{
				Utils::instaWrite(client.getFd(), ERR_UNKNOWNMODE(client.getUserByHexChat(), "+" + params[1][i]));
				return;
			}
		}
	}
	else if (params[1][0] == '-')
	{
		for (size_t i = 1; i < params[1].size(); i++)
		{
			if (params[1][i] == 'o')
			{
				if (params.size() == 2)
				{
					Utils::instaWrite(client.getFd(), ERR_NEEDMOREPARAMS(client.getUserByHexChat(), "MODE"));
					return;
				}
				if (isClientInRoom(room, params[2]) == false)
				{
					Utils::instaWrite(client.getFd(), ERR_NOSUCHNICK(room.getName(), params[2]));
					return;
				}
				if (room.isOperator(params[2]) == false)
				{
					Utils::instaWrite(client.getFd(), ERR_UNKNOWNMODE(client.getUserByHexChat(), "-" + params[1][i]));
					return;
				}
				Client &cli = getClientByNick(params[2]);
				room.removeOperator(cli);
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "-" + params[1][i], params[2]));
			}
			else if (params[1][i] == 'i')
			{
				room.setKeycode(room.getKeycode() ^ FLAG_INV);
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "-" + params[1][i], ""));
			}
			else if (params[1][i] == 't')
			{
				room.setKeycode(room.getKeycode() ^ FLAG_TOPIC);
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "-" + params[1][i], ""));
			}
			else if (params[1][i] == 'n')
			{
				room.setKeycode(room.getKeycode() ^ FLAG_NOOUTSIDE);
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "-" + params[1][i], ""));
			}
			else if (params[1][i] == 'l')
			{
				room.setKeycode(room.getKeycode() ^ FLAG_LIMIT);
				room.setChanelLimit(0);
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "-" + params[1][i], ""));
			}
			else if (params[1][i] == 'k')
			{
				room.setKeycode(room.getKeycode() ^ FLAG_KEY);
				room.setKey("");
				Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), params[0], "-" + params[1][i], ""));
			}
			else
			{
				Utils::instaWrite(client.getFd(), ERR_UNKNOWNMODE(client.getUserByHexChat(), "-" + params[1][i]));
				return;
			}
		}
	}
	else{
		Utils::instaWrite(client.getFd(), ERR_UNKNOWNMODE(client.getUserByHexChat(), params[1]));
	}
}

void	Server::mode(C_STR_REF input, Client &client){
	if (client.getIsRegistered() == false){
		Utils::instaWrite(client.getFd(), ERR_NOTREGISTERED(client.getUserByHexChat()));
	}
	if (input.empty()){
		Utils::instaWrite(client.getFd(), ERR_NEEDMOREPARAMS(client.getUserByHexChat(), "MODE"));
		return;
	}
	VECT_STR		params = Utils::ft_split(input, " ");
	if (params[0][0] == '#')
		this->modeChannel(params, client);
	else
	{
		Utils::instaWrite(client.getFd(), ERR_UNKNOWNMODE(client.getUserByHexChat(), input));
	}
}
