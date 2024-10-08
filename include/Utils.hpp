#pragma once


#define USAGE "./ircserv [port] [password]"

#include <string>
#include <vector>
#include "Define.hpp"

using std::string;
using std::vector;
class Client;

namespace Utils {
	int					ft_stoi(C_STR_REF str);
	void				clearBuffer(char *buffer, int size);
	std::string			ft_trim(C_STR_REF str, C_STR_REF delims);
	VECT_STR			ft_firstWord(C_STR_REF str);
	VECT_STR			ft_split(C_STR_REF str, C_STR_REF delims);
	bool				isEqualNonSensitive(const string& str1, const string& str2);
	std::string			getTime();
	void				instaWriteAll(std::vector<Client> clients, std::string message);
	void				instaWrite(int fd, std::string message);
	std::string			ft_join(C_VECT_STR_R vec, C_STR_REF delim, int start);
	void				instaSend(int fd, std::string message);
	int					getMaxFd(const vector<Client> &v, int serverfd);
	std::string			ft_getNick(const std::string& str);
	std::string			ft_itoa(int n);
}
