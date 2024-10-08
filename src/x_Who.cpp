#include "Client.hpp"
#include "Server.hpp"

#include "Exception.hpp"
#include "Utils.hpp"
#include "Define.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/*
4.5.1 Who query

      Command: WHO
   Parameters: [<name> [<o>]]

   The WHO message is used by a client to generate a query which returns
   a list of information which 'matches' the <name> parameter given by
   the client.  In the absence of the <name> parameter, all visible
   (users who aren't invisible (user mode +i) and who don't have a
   common channel with the requesting client) are listed.  The same
   result can be achieved by using a <name> of "0" or any wildcard which

   will end up matching every entry possible.

   The <name> passed to WHO is matched against users' host, server, real
   name and nickname if the channel <name> cannot be found.

   If the "o" parameter is passed only operators are returned according
   to the name mask supplied.

   Numeric Replies:

           ERR_NOSUCHSERVER
           RPL_WHOREPLY                    RPL_ENDOFWHO

   Examples:

   WHO *.fi                        ; List all users who match against
                                   "*.fi".

   WHO jto* o                      ; List all users with a match against
                                   "jto*" if they are an operator.

*/


#define RPL_WHOREPLY(nick, channel, user, host, server, nickname, hopsin, realname) (std::string(":") + "IRC" + " 352 " + nick + " " + channel + " " + user + " " + host + " " + server + " " + nickname + " " + hopsin + " :0 " + realname + "\r\n")
#define RPL_ENDOFWHO(nick, name) (std::string(":") + "IRC" + " 315 " + nick + " " + name + " :End of /WHO list.\r\n")

void Server::who(C_STR_REF str, Client &cli) {
    if (cli.getIsRegistered() == false){
        Utils::instaWrite(cli.getFd(), ERR_NOTREGISTERED(cli.getUserByHexChat()));
        return;
    }
    if (str.empty()){
        Utils::instaWrite(cli.getFd(), ERR_NONICKNAMEGIVEN(cli.getNick()));
        return;
    }

    std::string name = str;
    std::string o;
    std::string::size_type pos = str.find(' ');
    if (pos != std::string::npos){
        name = str.substr(0, pos);
        o = str.substr(pos + 1);
    }

    if (name == "0"){
        name = "";
    }

    if (o == "o"){
        o = "o";
    } else {
        o = "";
    }

    std::vector<Client>::iterator it;
    for (it = this->clients.begin(); it != this->clients.end(); it++) {
        if (name[0] == '#' && isClientInRoom(*it, name)) {
                Room    &room = getRoom(name);
                if (room.isOperator(it->getNick())){
                        Utils::instaWrite(cli.getFd(), RPL_WHOREPLY(cli.getNick(), name, it->getUserByHexChat(), it->_ip, "IRC", it->getNick(), "H@", it->getRealName()));
                }
                else {
                        Utils::instaWrite(cli.getFd(), RPL_WHOREPLY(cli.getNick(), name, it->getUserByHexChat(), it->_ip, "IRC", it->getNick(), "H", it->getRealName()));
                }
        }
        else if (it->getNick() == name) {
                Utils::instaWrite(cli.getFd(), RPL_WHOREPLY(cli.getNick(), name, it->getUserByHexChat(), it->_ip, "IRC", it->getNick(), "H", it->getRealName()));
        }
    }

    Utils::instaWrite(cli.getFd(), RPL_ENDOFWHO(cli.getNick(), name));
}