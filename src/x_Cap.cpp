
#include "Define.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include "Server.hpp"


void Server::cap(C_STR_REF params, Client &client)
{
	if (params.empty())
	{
		Utils::instaWrite(client.getFd(), "CAP LS\r\n");
	}
	else
	{
		if (params == "LS" || params == "LS 302")
		{
			client.setType(hexchat);
		}
		else if (params == "BOT")
		{
			client.setType(bot_cap);
		}
		else
		{
			Utils::instaWrite(client.getFd(), "Invalid parameters for CAP\n\r");
		}
	}
}