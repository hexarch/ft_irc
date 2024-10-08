#pragma once

#include <string>
#include <vector>
#include "Define.hpp"
#include <netinet/in.h>

using std::string;
using std::vector;


class Client
{
public:
	Client();
	Client(int fd, int port);
	Client(const Client &other);
	Client			&operator=(const Client &other);

	int				getFd() const;
	int				getPort() const;
	string			getBuffer() const;
	bool			getIsRegistered() const;
	bool			getIsPassworded() const;
	int				getType() const;

	vector<string>	&getmesagesFromServer();
	string		  	getNick() const;
	string		  	getUserName() const;
	string		  	getRealName() const;
	string		  	getHostName() const;
	string		  	getServerName() const;

	void			setHostName(C_STR_REF hostName);
	void			setServerName(C_STR_REF serverName);
	void			setNick(C_STR_REF nick);
	void			setRegistered(bool val);
	void			setPassworded(bool val);
	void			setBuffer(C_STR_REF str);
	void			setType(int type);

	void			setUserName(C_STR_REF userName);
	void			setRealName(C_STR_REF realName);
	string			getUserByHexChat() const;
	virtual			~Client();
	char			_ip[INET_ADDRSTRLEN]; // 123.123.123.123 + \0

	bool			operator==(const Client &rhs) const;
private:
	int				_type; // 1:hex 3:bot
	int				_fd;
	int				_port;
	string			buffer;
	vector<string>	_messagesFromServer;
	bool			isRegistered;
	bool			isPassworded;
	string			_nick;
	string			_userName;
	string			_hostName;
	string			_serverName;
	string			_realName;
};
