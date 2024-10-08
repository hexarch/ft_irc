#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include "Client.hpp"

#include "Exception.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Room.hpp"
#include "Utils.hpp"
#include "Define.hpp"
#include "TextEngine.hpp"

// /*
// 	4.1.6 Quit

// 	Command: QUIT
// 	Parameters: [<Quit message>]

// 	A client session is ended with a quit message.  The server must close
// 	the connection to a client which sends a QUIT message. If a "Quit
// 	Message" is given, this will be sent instead of the default message,
// 	the nickname.

// 	When netsplits (disconnecting of two servers) occur, the quit message

// 	is composed of the names of two servers involved, separated by a
// 	space.  The first name is that of the server which is still connected
// 	and the second name is that of the server that has become
// 	disconnected.

// 	If, for some other reason, a client connection is closed without the
// 	client  issuing  a  QUIT  command  (e.g.  client  dies and EOF occurs
// 	on socket), the server is required to fill in the quit  message  with
// 	some sort  of  message  reflecting the nature of the event which
// 	caused it to happen.

// 	Numeric Replies:
// 	        None.
// 	Examples:
// 	QUIT :Gone to have lunch        ; Preferred message format.
// */


void Server::quit(C_STR_REF params, Client &client) {
    string  message = params;
    if (params.empty()) {
        message = "Client has quited";
    }
    if (params[0] == ':') {
        message = params.substr(1);
    }
    for (VECT_ITER_CHA it = this->channels.begin(); it != this->channels.end(); it++) {
        if (it->isClientInChannel(client.getFd())) {
            if (it->getClients().size() == 1)
            {
                TextEngine::magenta("Room " + it->getName() + " has been deleted", TextEngine::printTime(std::cout)) << std::endl;
                it->removeClient(client.getFd());
                this->channels.erase(it);
                --it;
            }
            else if (it->isOperator(client)){
                it->removeClient(client.getFd());
                it->removeOperator(client);
                Utils::instaWriteAll(it->getClients(), RPL_QUIT(client.getUserByHexChat(), message));
                responseAllClientResponseToGui(client, *it);
            }
            else {
                it->removeClient(client.getFd());
                Utils::instaWriteAll(it->getClients(), RPL_QUIT(client.getUserByHexChat(), message));
                responseAllClientResponseToGui(client, *it);
            }
        }
    }

    if (FD_ISSET(client.getFd(), &writefds)) {
        FD_CLR(client.getFd(), &writefds);
    }
    if (FD_ISSET(client.getFd(), &readfds)) {
        FD_CLR(client.getFd(), &readfds);
    }

    close(client.getFd());

    TextEngine::blue("Client ", TextEngine::printTime(cout)) << client._ip << ":" << client.getPort()<< " " << client.getNick() << " quited !" << std::endl;

    removeClient(client.getFd());
}