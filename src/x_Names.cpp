#include "Client.hpp"

#include "Exception.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Room.hpp"
#include "Utils.hpp"
#include "Define.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

/*
    Command: NAMES
    Parameters: [<channel>{,<channel>}]

    By using the NAMES command, a user can list all nicknames that are
    visible to them on any channel that they can see.  Channel names
    which they can see are those which aren't private (+p) or secret (+s)
    or those which they are actually on.  The <channel> parameter
    specifies which channel(s) to return information about if valid.
    There is no error reply for bad channel names.

    If no <channel> parameter is given, a list of all channels and their
    occupants is returned.  At the end of this list, a list of users who
    are visible but either not on any channel or not on a visible channel
    are listed as being on `channel' "*".

    Numerics:

            RPL_NAMREPLY                    RPL_ENDOFNAMES

    Examples:

    NAMES #twilight_zone,#42        ; list visible users on #twilight_zone
                                    and #42 if the channels are visible to
                                    you.

    NAMES                           ; list all visible channels and users
*/

void    Server::names(C_STR_REF params, Client &fd){
    if (fd.getIsRegistered() == false){
        Utils::instaWrite(fd.getFd(), ERR_NOTREGISTERED(fd.getNick()));
        return;
    }
    if (params[0] != '#'){
        string  userSTR;
        for (VECT_ITER_CLI it = clients.begin(); it != clients.end(); it++){
            userSTR += it->getNick() + " ";
        }
        Utils::instaWrite(fd.getFd(), RPL_NAMREPLY(fd.getNick(), "*", userSTR));
        Utils::instaWrite(fd.getFd(), RPL_ENDOFNAMES(fd.getNick(), "*"));
    }
    else{
        VECT_STR splitted = Utils::ft_split(params, ",");
        for (vector<string>::iterator it = splitted.begin(); it != splitted.end(); it++){
            bool found = false;
            for (VECT_ITER_CHA it2 = channels.begin(); it2 != channels.end(); it2++){
                if ((*it2).getName() == *it){
                    string message;
                    for (VECT_ITER_CLI it3 = it2->getClients().begin(); it3 != it2->getClients().end(); it3++){
                        if (it2->isOperator(*it3))
                            message += "@";
                        message += (*it3).getNick() + " ";
                    }
                    Utils::instaWrite(fd.getFd(), RPL_NAMREPLY(fd.getNick(), *it, message));
                    Utils::instaWrite(fd.getFd(), RPL_ENDOFNAMES(fd.getNick(), *it));
                    found = true;
                    break;
                }
            }
            if (!found)
                Utils::instaWrite(fd.getFd(), ERR_NOSUCHCHANNEL(fd.getNick(), *it));
        }
    }
}
