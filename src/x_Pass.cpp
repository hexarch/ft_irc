#include "Client.hpp"
#include "Server.hpp"
#include "Exception.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "Utils.hpp"
#include "ErrorRPL.hpp"
#include "Define.hpp"
#include "TextEngine.hpp"

/*
	4.1.1 Password message


	Command: PASS
	Parameters: <password>

	The PASS command is used to set a 'connection password'.  The
	password can and must be set before any attempt to register the
	connection is made.  Currently this requires that clients send a PASS
	command before sending the NICK/USER combination and servers *must*
	send a PASS command before any SERVER command.  The password supplied
	must match the one contained in the C/N lines (for servers) or I
	lines (for clients).  It is possible to send multiple PASS commands
	before registering but only the last one sent is used for
	verification and it may not be changed once registered.  Numeric
	Replies:

	    ERR_NEEDMOREPARAMS              ERR_ALREADYREGISTRED

	Example:
	    PASS secretpasswordhere
*/

#define RPL_PASS(source, nick) (string(":") + source + " 001 " + " :Password accepted\r\n")

void Server::pass(C_STR_REF params, Client &client){
	if (params.empty()){
		Utils::instaWrite(client.getFd(), ERR_NEEDMOREPARAMS(client.getUserByHexChat(), "PASS"));
	}
	else if (client.getIsPassworded()){
		Utils::instaWrite(client.getFd(), ERR_ALREADYREGISTRED(client.getUserByHexChat()));
	}
	else if (params != password){
		Utils::instaWrite(client.getFd(), ERR_PASSWDMISMATCH(client.getUserByHexChat()));
		quit("", client);
	}
	else{
		client.setPassworded(true);
		Utils::instaWrite(client.getFd(), RPL_PASS(client.getUserByHexChat(), client.getNick()));
	}
}
