/*

    Command: INVITE
    Parameters: <nickname> <channel>

    The INVITE message is used to invite users to a channel.  The
    parameter <nickname> is the nickname of the person to be invited to
    the target channel <channel>.  There is no requirement that the
    channel the target user is being invited to must exist or be a valid
    channel.  To invite a user to a channel which is invite only (MODE
    +i), the client sending the invite must be recognised as being a
    channel operator on the given channel.

    Numeric Replies:

            ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
            ERR_NOTONCHANNEL                ERR_USERONCHANNEL
            ERR_CHANOPRIVSNEEDED
            RPL_INVITING                    RPL_AWAY

    Examples:

    :Angel INVITE Wiz #Dust         ; User Angel inviting WiZ to channel
                                    #Dust

    INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
                                    #Twilight_zone

*/

#include "Client.hpp"

#include "Exception.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Room.hpp"
#include "Utils.hpp"
#include "TextEngine.hpp"
#include "Define.hpp"
#include "ErrorRPL.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

bool    Server::isClient(C_STR_REF nickname)
{
        for (size_t i = 0; i < clients.size(); i++)
        {
                if (clients[i].getNick() == nickname)
                        return (true);
        }
        return (false);
}

#define RPL_INVITE_TO_CLIENT(source, target, channel) (string(":") + source + " INVITE " + target + " :" + channel + "\r\n")

void    Server::invite(C_STR_REF input, Client &client)
{
        if (client.getIsRegistered() == false)
        {
                Utils::instaWrite(client.getFd(), ERR_NOTREGISTERED(client.getUserByHexChat()));
                return;
        }
        VECT_STR       params = Utils::ft_split(input, " ");
        if (params.size() < 2)
        {
                Utils::instaWrite(client.getFd(), ERR_NEEDMOREPARAMS(client.getUserByHexChat(),"INVITE"));
                return;
        }
        string nickname = params[0];
        string channel = params[1];
        if (isRoom(channel) == false)
        {
                Utils::instaWrite(client.getFd(), ERR_NOSUCHCHANNEL(client.getUserByHexChat(),channel));
                return;
        }
        Room &room = getRoom(channel);
        if (isClientInRoom(room, client) == false)
        {
                Utils::instaWrite(client.getFd(), ERR_NOTONCHANNEL(client.getUserByHexChat(),channel));
                return;
        }
        if (room.isOperator(client) == false)
        {
                Utils::instaWrite(client.getFd(), ERR_CHANOPRIVSNEEDED(client.getUserByHexChat(),channel));
                return;
        }
        if (isClientInRoom(room, nickname) == true)
        {
                Utils::instaWrite(client.getFd(), ERR_USERONCHANNEL(nickname,nickname));
                return;
        }
        if (isClient(nickname) == false)
        {
                Utils::instaWrite(client.getFd(), ERR_NOSUCHNICK(client.getUserByHexChat(), nickname));
                return;
        }
        Client &target = getClientByNick(nickname);
        Utils::instaWrite(target.getFd(), RPL_INVITE_TO_CLIENT(client.getUserByHexChat(),nickname,channel));
        Utils::instaWrite(client.getFd(), RPL_INVITING(client.getUserByHexChat(),nickname,channel));
        room.addInvite(target);
}
