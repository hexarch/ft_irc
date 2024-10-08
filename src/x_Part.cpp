#include "Client.hpp"
#include "Exception.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Room.hpp"
#include "Utils.hpp"
#include "TextEngine.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Define.hpp"
#include <stdlib.h>

/*
	4.2.2 Part message

	Command: PART
	Parameters: <channel>{,<channel>}

	The PART message causes the client sending the message to be removed
	from the list of active users for all given channels listed in the
	parameter string.

	Numeric Replies:

	        ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
	        ERR_NOTONCHANNEL

	Examples:

	PART #twilight_zone             ; leave channel "#twilight_zone"

	PART #oz-ops,&group5            ; leave both channels "&group5" and
                                   "#oz-ops".
*/

void Server::part(C_STR_REF params, Client &client)
{
	if (client.getIsRegistered() == false){
		Utils::instaWrite(client.getFd(), ERR_NOTREGISTERED(client.getUserByHexChat()));
		return ;
	}
	if (params.empty())
	{
		Utils::instaWrite(client.getFd(), ERR_NEEDMOREPARAMS(client.getNick(), "PART"));
		return ;
	}
	VECT_STR param = Utils::ft_split(params, " ");
	if (param[0][0] != '#'){
		param[0] = "#" + param[0];
	}
	if (isRoom(param[0])){
		Room &room = getRoom(param[0]);
		vector<Room>::iterator it = channels.begin();
		string reason = (param.size() > 1) ? Utils::ft_join(param, " ", 1) : "";
		if (reason[0] == ':')
			reason = reason.substr(1, reason.size() - 1);
		for (; it != channels.end(); ++it)
		{
			if (it->getName() == param[0])
				break;
		}
		if (!room.isClientInChannel(client.getFd())){
			Utils::instaWrite(client.getFd(), ERR_NOTONCHANNEL(client.getNick(), room.getName()));
			return ;
		}
		if (room.getClients().size() == 1) // delete room
		{
			TextEngine::magenta("Room " + room.getName() + " has been deleted", TextEngine::printTime(std::cout)) << std::endl;
			it->removeClient(client.getFd());
			channels.erase(it);
			Utils::instaWrite(client.getFd(), RPL_PART(client.getUserByHexChat(), param[0], reason));
			return ;
		}
		else if (room.isOperator(client)) // if client is operator
		{
			room.removeOperator(client);
		}
		Utils::instaWriteAll(room.getClients(), RPL_PART(client.getUserByHexChat(), param[0], reason));
		room.removeClient(client.getFd());
		responseAllClientResponseToGui(client, room);
	}
	else
	{
		Utils::instaWrite(client.getFd(), ERR_NOSUCHCHANNEL(client.getNick(), param[0]));
	}
}
