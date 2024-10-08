#include "Utils.hpp"
#include "Exception.hpp"
#include "Client.hpp"
#include "TextEngine.hpp"
#include "Room.hpp"
#include "Define.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include <vector>

using namespace std;
#define VECT_STR std::vector<std::string>

int	Utils::ft_stoi(C_STR_REF str)
{
	int		result = 0;
	int		sign = 1;
	int		i = 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			throw Exception("Invalid Port Conversion");
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}


string	Utils::ft_trim(const string& str, C_STR_REF delims){
	size_t first = str.find_first_not_of(delims);
	size_t last = str.find_last_not_of(delims);
	return str.substr(first, (last - first + 1));
}

void	Utils::clearBuffer(char *buffer, int size)
{
	for (int i = 0; i < size; i++)
	{
		buffer[i] = '\0';
	}
}

VECT_STR	Utils::ft_split(const string& str, C_STR_REF delims){
	VECT_STR	result;
	size_t		start = 0;
	size_t		end = 0;

	while (end != string::npos)
	{
		start = str.find_first_not_of(delims, end);
		if (start == string::npos)
			break ;
		end = str.find_first_of(delims, start);
		result.push_back(str.substr(start, end - start));
	}
	return (result);
}


bool	Utils::isEqualNonSensitive(const string& str1, const string& str2)
{
	if (str1.size() != str2.size())
		return false;
	for (size_t i = 0; i < str1.size(); i++)
	{
		if (tolower(str1[i]) != tolower(str2[i]))
			return false;
	}
	return true;
}

std::string Utils::getTime()
{
	time_t now = time(0);
		tm *ltm = localtime(&now);
		std::stringstream ss;
		ss 	<< std::setfill('0') << std::setw(2) << ltm->tm_mday << '-'
			<< std::setfill('0') << std::setw(2) << (1 + ltm->tm_mon) << '-'
			<< std::setfill('0') << std::setw(4) << (1900 + ltm->tm_year) << ' '
			<< std::setfill('0') << std::setw(2) << ltm->tm_hour << ':'
			<< std::setfill('0') << std::setw(2) << ltm->tm_min << ':'
			<< std::setfill('0') << std::setw(2) << ltm->tm_sec;
		return ss.str();
}

void Utils:: instaWrite(int fd, std::string message) {

    if (write(fd, message.c_str(), message.length()) < 0) {
		TextEngine::red("Error: message send", TextEngine::printTime(std::cout));
        return;
    }
}

void	Utils::instaSend(int fd, std::string message)
{
	if (send(fd, message.c_str(), message.length(), 0) < 0)
	{
		TextEngine::red("Error: message send", TextEngine::printTime(std::cout));
	}
}

void	Utils::instaWriteAll(VECT_CLI clients, std::string message)
{
	for (VECT_ITER_CLI it = clients.begin(); it != clients.end(); it++)
	{
		Utils::instaWrite((*it).getFd(), message);
	}
}

VECT_STR	Utils::ft_firstWord(C_STR_REF str)
{
	VECT_STR	result;
	size_t		start = 0;
	size_t		end = 0;

	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
		{
			end = i;
			break ;
		}
	}
	if (end == 0)
	{
		result.push_back(ft_trim(str, " "));
		result.push_back("");
		return (result);
	}
	result.push_back(ft_trim(str.substr(start, end), " "));
	result.push_back(ft_trim(str.substr(end, str.size() - end), " "));
	return (result);
}

std::string	Utils::ft_join(C_VECT_STR_R vec, C_STR_REF delim, int start)
{
	std::string result = "";
	for (size_t i = start; i < vec.size(); i++)
	{
		result += vec[i];
		if (i + 1 < vec.size())
			result += delim;
	}
	return result;
}

int	Utils::getMaxFd(C_VECT_CLI_R vec,int server){
	if (vec.size() == 0){
		return (server);
	}
	int		max = vec[0].getFd();
	for (vector<Client>::const_iterator it = vec.begin(); it != vec.end(); ++it){
		if (max < it->getFd()){
			max = it->getFd();
		}
	}
	return (max);
}


std::string	Utils::ft_getNick(const std::string& str)
{
	size_t		start = 1;
	size_t		end = 0;

	for (size_t i = 1; i < str.size(); i++)
	{
		if (str[i] == '!')
		{
			end = i;
			break ;
		}
	}
	return (str.substr(start, end - start));
}

std::string	Utils::ft_itoa(int n)
{
	std::string result;
	std::stringstream ss;
	ss << n;
	ss >> result;
	return result;
}

