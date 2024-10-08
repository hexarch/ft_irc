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
4.5.2 Whois query

      Command: WHOIS
   Parameters: [<server>] <nickmask>[,<nickmask>[,...]]

   This message is used to query information about particular user.  The
   server will answer this message with several numeric messages
   indicating different statuses of each user which matches the nickmask
   (if you are entitled to see them).  If no wildcard is present in the
   <nickmask>, any information about that nick which you are allowed to
   see is presented.  A comma (',') separated list of nickNames may be
   given.

   The latter version sends the query to a specific server.  It is
   useful if you want to know how long the user in question has been
   idle as only local server (ie. the server the user is directly
   connected to) knows that information, while everything else is
   globally known.

   Numeric Replies:

           ERR_NOSUCHSERVER(no)                ERR_NONICKNAMEGIVEN(done)
           RPL_WHOISUSER                   RPL_WHOISCHANNELS
           RPL_WHOISCHANNELS               RPL_WHOISSERVER(no)
           RPL_AWAY                        RPL_WHOISOPERATOR(no)
           RPL_WHOISIDLE                   ERR_NOSUCHNICK
           RPL_ENDOFWHOIS
   Examples:

   WHOIS wiz                       ; return available user information
                                   about nick WiZ

   WHOIS eff.org trillian          ; ask server eff.org for user
                                   information about trillian

*/

void	Server::whois(C_STR_REF str, Client &cli){
        if (cli.getIsRegistered() == false){
            Utils::instaWrite(cli.getFd(), ERR_NOTREGISTERED(cli.getUserByHexChat()));
            return;
        }
        if (str.empty()){
            Utils::instaWrite(cli.getFd(), ERR_NONICKNAMEGIVEN(cli.getNick()));
            return;
        }
        std::vector<std::string> vec = Utils::ft_split(str, " ");
        for (size_t i = 0; i < vec.size(); i++){
                for (size_t j = 0; j < clients.size(); j++){
                        if (clients[j].getNick() == vec[i]){
                                Utils::instaWrite(cli.getFd(), RPL_WHOISUSER(cli.getNick(),clients[j].getNick(), clients[j].getUserName(), clients[j].getHostName(), clients[j].getRealName()));
                                for (size_t k = 0; k < channels.size(); k++){
                                        if ((isClientInRoom(channels[k], clients[j]) && isClientInRoom(channels[k], cli)))
                                                Utils::instaWrite(cli.getFd(), RPL_WHOISCHANNELS(cli.getNick(), clients[j].getNick(), channels[k].getName()));
                                }
                                Utils::instaWrite(cli.getFd(), RPL_ENDOFWHOIS(cli.getNick(), clients[j].getNick()));
                                return;
                        }
                }
        }

}
