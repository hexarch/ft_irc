#include "Client.hpp"
#include "Server.hpp"
#include "Exception.hpp"
#include "Utils.hpp"
#include "Define.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Define.hpp"

/*
	4.2.4 Topic message

	      Command: TOPIC
	   Parameters: <channel> [<topic>]

	   The TOPIC message is used to change or view the topic of a channel.
	   The topic for channel <channel> is returned if there is no <topic>
	   given.  If the <topic> parameter is present, the topic for that
	   channel will be changed, if the channel modes permit this action.

	   Numeric Replies:

	           ERR_NEEDMOREPARAMS (done)       ERR_NOTONCHANNEL (done)
	           RPL_NOTOPIC                     RPL_TOPIC
	           ERR_CHANOPRIVSNEEDED

	   Examples:

	   :Wiz TOPIC #test :New topic     ;User Wiz setting the topic.

	   TOPIC #test :another topic      ;set the topic on #test to "another
	                                   topic".

	   TOPIC #test                     ; check the topic for #test.
*/

void Server::topic(C_STR_REF command, Client &client)
{
	if (client.getIsRegistered() == false){
		Utils::instaWrite(client.getFd(), ERR_NOTREGISTERED(client.getUserByHexChat()));
		return;
	}
	if (command.empty())
	{
		Utils::instaWrite(client.getFd(), ERR_NEEDMOREPARAMS(client.getNick(), "TOPIC"));
		return;
	}
	VECT_STR params = Utils::ft_split(command, " ");

	if (isRoom(params[0])){
		Room &room = getRoom(params[0]);
		if (!room.isClientInChannel(client.getFd())){
			Utils::instaWrite(client.getFd(), ERR_NOTONCHANNEL(client.getNick(), room.getName()));
			return;
		}
		if (params.size() == 1){
			if (room.getTopic().empty()){
				Utils::instaWrite(client.getFd(), RPL_NOTOPIC(client.getUserByHexChat(), room.getName()));
			}
			else{
				Utils::instaWrite(client.getFd(), RPL_TOPIC(client.getUserByHexChat(), room.getName(), room.getTopic()));
			}
			return;
		}
		if (room.getKeycode() & FLAG_TOPIC && !room.isOperator(client))
		{
			Utils::instaWrite(client.getFd(), ERR_CHANOPRIVSNEEDED(client.getUserByHexChat(), room.getName()));
			return;
		}
		string newtopic = Utils::ft_join(params, " ", 1);
		if (newtopic[0] != ':')
			newtopic = ":" + newtopic;
		string oldtopic = room.getTopic();
		room.setTopic(newtopic);
		Utils::instaWriteAll(room.getClients(), RPL_TOPIC(client.getUserByHexChat(), room.getName(), newtopic));
		if (oldtopic != newtopic)
		{
			time_t	now = time(0);
			string response = Utils::ft_itoa(now);
			Utils::instaWriteAll(room.getClients(), RPL_TOPICSET(client.getUserByHexChat(), room.getName(), client.getNick(), response));
		}
		return;
	}
	else {
		Utils::instaWrite(client.getFd(), ERR_NOSUCHCHANNEL(client.getNick(), params[0]));
		return;
	}
}
