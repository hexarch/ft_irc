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

/*
4.4.2 Notice

      Command: NOTICE
   Parameters: <nickname> <text>

   The NOTICE message is used similarly to PRIVMSG.  The difference
   between NOTICE and PRIVMSG is that automatic replies must never be
   sent in response to a NOTICE message.  This rule applies to servers
   too - they must not send any error reply back to the client on
   receipt of a notice.  The object of this rule is to avoid loops
   between a client automatically sending something in response to
   something it received.  This is typically used by automatons (clients
   with either an AI or other interactive program controlling their
   actions) which are always seen to be replying lest they end up in a
   loop with another automaton.

   See PRIVMSG for more details on replies and examples.

	PRIV

	   Numeric Replies:

           ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
           ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
           ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
           ERR_NOSUCHNICK
           RPL_AWAY

   Examples:

:Angel PRIVMSG Wiz :Hello are you receiving this message ?
                                ; Message from Angel to Wiz.

PRIVMSG Angel :yes I'm receiving it !receiving it !'u>(768u+1n) .br ;
                                Message to Angel.

PRIVMSG jto@tolsun.oulu.fi :Hello !
                                ; Message to a client on server

                                tolsun.oulu.fi with username of "jto".

PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.
                                ; Message to everyone on a server which
                                has a name matching *.fi.

PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions
                                ; Message to all users who come from a
                                host which has a name matching *.edu.
*/


namespace
        {
        int isInRoom(Client &client, Server &server, std::string room) {
        	for (VECT_ITER_CHA it = server.getRooms().begin(); it != server.getRooms().end(); it++) {
        		if (it->getName() == room) {
        			for (VECT_ITER_CLI it2 = it->getClients().begin(); it2 != it->getClients().end(); it2++) {
        				if (it2->getFd() == client.getFd())
        					return 1;
        			}
        		}
        	}
        	return 0;
        }
}

void	Server::notice(C_STR_REF input, Client &client){
	if (!client.getIsRegistered())
	{
		Utils::instaWrite(client.getFd(), ERR_NOTREGISTERED(client.getUserByHexChat()));
		return;
	}
	if (input.empty())
	{
		Utils::instaWrite(client.getFd(), ERR_NORECIPIENT(client.getUserByHexChat(), "NOTICE"));
		return;
	}
	VECT_STR	tokns = Utils::ft_split(input, " ");
	if (tokns.size() < 2)
	{
		Utils::instaWrite(client.getFd(), ERR_NOTEXTTOSEND(client.getUserByHexChat()));
		return;
	}
	string receiver = tokns[0];
	string message = Utils::ft_join(tokns, " ", 1);
	if (message[0] == ':')
		message = message.substr(1);
	if (receiver[0] == '#')
	{
		if (isRoom(receiver)){
			Room &room = getRoom(receiver);
			if (isInRoom(client, *this, receiver))
            {
                for (VECT_ITER_CLI it = room.getClients().begin(); it != room.getClients().end(); it++)
                {
                        if (it->getFd() != client.getFd())
                        {
							Utils::instaWrite(it->getFd(), RPL_NOTICE(client.getUserByHexChat(), receiver, message));
		                }
                }
			}
            else {
				if (!(room.getKeycode() & FLAG_NOOUTSIDE))
				{
					for (VECT_ITER_CLI it = room.getClients().begin(); it != room.getClients().end(); it++)
                	{
                	        if (it->getFd() != client.getFd())
                	        {
								Utils::instaWrite(it->getFd(), RPL_NOTICE(client.getUserByHexChat(), receiver, message));
		        	        }
                	}
				}
				else {
                    Utils::instaWrite(client.getFd(), ERR_CANNOTSENDTOCHAN(client.getUserByHexChat(), receiver));
                    return;
				}
            }
		}
		else{
			Utils::instaWrite(client.getFd(), ERR_NOSUCHCHANNEL(client.getUserByHexChat(), receiver));
            return;
		}
	}
	else
	{
		bool isExist = false;
		for (VECT_ITER_CLI it = clients.begin(); it != clients.end(); it++)
		{
			if (it->getNick() == receiver)
			{
				isExist = true;
				Utils::instaWrite(it->getFd(), RPL_NOTICE(client.getUserByHexChat(), receiver, message));
				return;
			}
		}
		if (!isExist)
			Utils::instaWrite(client.getFd(), ERR_NOSUCHNICK(client.getUserByHexChat(), receiver));
	}
}
