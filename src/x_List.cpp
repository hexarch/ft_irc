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
    Command: LIST
    Parameters: [<channel>{,<channel>} [<server>]]

    The list message is used to list channels and their topics.  If  the
    <channel>  parameter  is  used,  only  the  status  of  that  channel
    is displayed.  Private  channels  are  listed  (without  their
    topics)  as channel "Prv" unless the client generating the query is
    actually on that channel.  Likewise, secret channels are not listed

    at  all  unless  the client is a member of the channel in question.

    Numeric Replies:

            ERR_NOSUCHSERVER                RPL_LISTSTART
            RPL_LIST                        RPL_LISTEND

    Examples:

    LIST                            ; List all channels.

    LIST #twilight_zone,#42         ; List channels #twilight_zone and #42
*/

namespace {
    string intToString(int num){
        std::stringstream ss;
        ss << num;
        return ss.str();
    }
}

void    Server::list(C_STR_REF params, Client &fd){
    if (fd.getIsRegistered() == false){
        Utils::instaWrite(fd.getFd(), ERR_NOTREGISTERED(fd.getUserByHexChat()));
        return ;
    }
    if (params.empty()){
        Utils::instaWrite(fd.getFd(), RPL_LISTSTART(fd.getNick(), intToString(channels.size())));
        for (VECT_ITER_CHA it = channels.begin(); it != channels.end(); it++){
            if (it->getTopic().empty()){
                Utils::instaWrite(fd.getFd(), RPL_LIST(fd.getNick(), it->getName(), intToString(it->getClients().size()), " Empty"));
            }
            else{
                Utils::instaWrite(fd.getFd(), RPL_LIST(fd.getNick(), it->getName(), intToString(it->getClients().size()), it->getTopic()));
            }
        }
        Utils::instaWrite(fd.getFd(), RPL_LISTEND(fd.getNick()));
    }
    else {
        vector<string> splitted = Utils::ft_split(params, ",");
        for (VECT_STR::iterator it = splitted.begin(); it != splitted.end(); it++){
            bool found = false;
            for (VECT_ITER_CHA it2 = channels.begin(); it2 != channels.end(); it2++){
                if (*it == it2->getName()){
                    found = true;
                    if (it2->getTopic().empty()){
                        Utils::instaWrite(fd.getFd(), RPL_LIST(fd.getNick(), it2->getName(), intToString(it2->getClients().size()), " Empty"));
                    }
                    else{
                        Utils::instaWrite(fd.getFd(), RPL_LIST(fd.getNick(), it2->getName(), intToString(it2->getClients().size()), it2->getTopic()));
                    }
                }
            }
            if (found == false){
                Utils::instaWrite(fd.getFd(), ERR_NOSUCHCHANNEL(fd.getNick(), *it));
            }
        }
    }
}
