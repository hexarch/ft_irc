#pragma once

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <string>

#include "Utils.hpp"

class Bot {
	public:
		Bot(C_STR_REF port, C_STR_REF password);
		~Bot();
		void	run();
		void	initSocket();

	private:
		std::string			_name;
		int					_socket;
		int					_port;
		std::string			_password;
		struct sockaddr_in	_bot_addr;
		char				_buffer[1024];

};
