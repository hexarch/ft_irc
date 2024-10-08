#include "Client.hpp"
#include "Room.hpp"
#include "Server.hpp"
#include "Exception.hpp"
#include "Define.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Define.hpp"

// op channel user

#define ERR_ALREADYOPERATOR(nick, channel) (string(":") + "IRC" + " 482 " + nick + " " + channel + " :You're already an operator\r\n")

void Server::op(C_STR_REF params, Client &client)
{
	if (client.getIsRegistered() == false)
	{
		Utils::instaWrite(client.getFd(), ERR_NOTREGISTERED(client.getNick()));
		return;
	}
	VECT_STR splitFirst = Utils::ft_split(params, " ");
	if (splitFirst.size() < 2)
	{
		Utils::instaWrite(client.getFd(), ERR_NEEDMOREPARAMS(client.getNick(), "OP"));
		return;
	}
	string channel = splitFirst[0];
	string user = splitFirst[1];
	if (isRoom(channel) == false)
	{
		Utils::instaWrite(client.getFd(), ERR_NOSUCHCHANNEL(client.getNick(), channel));
		return;
	}
	Room &room = getRoom(channel);
	if (isClientInRoom(room, client) == false)
	{
		Utils::instaWrite(client.getFd(), ERR_NOTONCHANNEL(client.getNick(), channel));
		return;
	}
	if (room.isOperator(client) == false)
	{
		Utils::instaWrite(client.getFd(), ERR_CHANOPRIVSNEEDED(client.getNick(), channel));
		return;
	}
	if (isClient(user) == false)
	{
		Utils::instaWrite(client.getFd(), ERR_NOSUCHNICK(client.getNick(), user));
		return;
	}
	Client &target = getClientByNick(user);
	if (isClientInRoom(room, target) == false)
	{
		Utils::instaWrite(client.getFd(), ERR_USERNOTINCHANNEL(user, channel));
		return;
	}
	if (room.isOperator(target) == true)
	{
		Utils::instaWrite(client.getFd(), ERR_ALREADYOPERATOR(client.getNick(), channel));
		return;
	}
	room.addOperator(target);
	Utils::instaWriteAll(room.getClients(), RPL_MODE(client.getUserByHexChat(), splitFirst[0], "+o", splitFirst[1]));
}
