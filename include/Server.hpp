#pragma once

#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Define.hpp"
#include "Room.hpp"
#include "CommandRPL.hpp"
#include "ErrorRPL.hpp"

#include <unistd.h>
#include <map>

using std::string;
using std::vector;

class Client;
class Room;

class Server
{
public:
	Server(C_STR_REF port, C_STR_REF password);
	virtual ~Server();
	void run();
	void join(C_STR_REF params, Client &client);
	void part(C_STR_REF params, Client &client);
	void privmsg(C_STR_REF command, Client &client);
	void op(C_STR_REF params, Client &client);
	void mode(C_STR_REF params, Client &client);
	void nick(C_STR_REF params, Client &client);
	void who(C_STR_REF command, Client &client);
	void topic(C_STR_REF command, Client &client);
	void ping(C_STR_REF params, Client &client);
	void quit(C_STR_REF params, Client &client);
	void whois(C_STR_REF, Client &cli);
	void list(C_STR_REF params, Client &client);
	void names(C_STR_REF params, Client &fd);
	void notice(C_STR_REF input, Client &fd);
	void kick(C_STR_REF input, Client &fd);
	void user(C_STR_REF params, Client &client);
	void cap(C_STR_REF params, Client &client);
	void pass(C_STR_REF param, Client &client);
	void invite(C_STR_REF input, Client &client);
	bool isClient(C_STR_REF nickname);

	Room &getRoom(C_STR_REF name);

	vector<Room> &getRooms();

	bool isRoom(C_STR_REF name);

	void addRoom(const Room &room);
	void addClient(const Client &client);

	vector<Client> &getClients();

	void	responseAllClientResponseToGui(Client &client, Room &room);
	bool	isClientInRoom(Room &room, const Client &client);
	bool	isClientInRoom(Client &client, string &room);
	bool	isClientInRoom(Room &room, string &nick);
	void	removeClient(int fd);

	Client	&getClientByNick(C_STR_REF nick);

	int		getSocket() const { return this->_socket; }

private:
	Server();
	Server(const Server &other);
	Server &operator=(const Server &other);
	void	initSocket();
	void	initFunctions();
	void	modeChannel(VECT_STR &params, Client &client);
	void	runCommand(C_STR_REF command, Client &client);

	int					port;
	string				password;
	int					_socket;
	struct sockaddr_in	address;
	struct sockaddr_in	clientAddress;

	fd_set readfds;
	fd_set writefds;
	/*
		The reason for storing file descriptors in supplementary sets (this->readFdsSup and this->writeFdsSup)
		instead of directly modifying the original sets (this->readFds and this->writeFds) is to avoid race conditions
		and to ensure that the original sets remain unchanged for the next iteration of the loop.


		avoid blocking sockets we need to use select() function
		and copy the original sets to supplementary sets
	*/
	fd_set				writeFdsCopy;
	fd_set				readFdsCopy;

	vector<Client>		clients;
	vector<Room>		channels;

	char				buffer[1024];
	std::map<std::string, void (Server::*)(const std::string &, Client &)> _commands;
};
