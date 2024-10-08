#include "Client.hpp"
#include "Server.hpp"
#include "ErrorRPL.hpp"
#include "CommandRPL.hpp"
#include "Utils.hpp"
#include "Exception.hpp"
#include "TextEngine.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Define.hpp"

/*
   Parameters: <username> <hostname> <servername> <realname>
   1.  ERR_ALREADYREGISTRED
   2.  ERR_NEEDMOREPARAMS
   since only after both USER and NICK have been
   received from a client does a user become registered.

   It must be noted that realname parameter must be the last parameter,
   because it may contain space characters and must be prefixed with a
   colon (':') to make sure this is recognised as such.
*/


void	Server::user(C_STR_REF params, Client &client)
{
	if (!client.getIsPassworded()){
		Utils::instaWrite(client.getFd(), ERR_NOTPASSWORDED(client.getUserByHexChat()));
		return ;
	}
	vector<string> v = Utils::ft_split(params, " ");
	if (v.size() < 4){
		Utils::instaWrite(client.getFd(), ERR_NEEDMOREPARAMS(client.getUserByHexChat(), "USER"));
		return ;
	}
	if (client.getIsRegistered()){
		Utils::instaWrite(client.getFd(), ERR_ALREADYREGISTRED(client.getUserByHexChat()));
		return ;
	}
	string username = v[0];
	string hostname = v[1];
	string servername = v[2];
	string realname = Utils::ft_join(v, " ", 3);
	client.setUserName(username);
	client.setHostName(hostname);
	client.setServerName(servername);
	if (realname[0] == ':')
		realname = realname.substr(1);
	client.setRealName(realname);
	if (client.getNick().empty())
		return ;
	if (!client.getIsRegistered()){
		client.setRegistered(true);
		Utils::instaWrite(client.getFd(), RPL_WELCOME(client.getNick(), client.getUserByHexChat()));
		TextEngine::magenta("User " + client.getNick() + " has been registered", TextEngine::printTime(std::cout)) << std::endl;
	}
}
