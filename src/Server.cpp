#include "Server.hpp"
#include "Exception.hpp"
#include "Utils.hpp"
#include "TextEngine.hpp"
#include "Client.hpp"
#include "ErrorRPL.hpp"
#include "CommandRPL.hpp"
#include "Room.hpp"
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include "Define.hpp"
#include <fcntl.h>

using std::cout;

Server::Server(C_STR_REF port, C_STR_REF password)
	: port(0), password(password)
{
	try
	{
		this->port = Utils::ft_stoi(port);
		if (this->port < 0 || this->port > 65535)
		{
			throw Exception("Invalid port");
		}
		initSocket();
		initFunctions();
	}
	catch (const Exception &e)
	{
		throw e;
	}
}

Server::Server(const Server &other)
	: port(other.port), password(other.password)
{
	*this = other;
}

Server &Server::operator=(const Server &other)
{
	if (this != &other)
	{
		this->port = other.port;
		this->password = other.password;
		this->_socket = other._socket;
		this->clients = other.clients;
		this->channels = other.channels;
		this->clientAddress = other.clientAddress;
		this->address = other.address;
		this->readfds = other.readfds;
		this->writefds = other.writefds;
		this->readFdsCopy = other.readFdsCopy;
		this->writeFdsCopy = other.writeFdsCopy;
	}
	return *this;
}

Server::~Server()
{
	for (VECT_ITER_CLI it = clients.begin(); it != clients.end(); it++)
	{
		close(it->getFd());
	}
	if (this->_socket > 0)
	{
		close(this->_socket);
	}
	this->clients.clear();
	this->channels.clear();
	TextEngine::red("Server closed", TextEngine::printTime(cout)) << std::endl;
}

void Server::run()
{
	socklen_t templen = sizeof(sockaddr_in);
 	bool isReadyToSelect = true;
	int bytesRead = 0;

	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&readFdsCopy);
	FD_ZERO(&writeFdsCopy);

	FD_SET(this->_socket, &readfds);
	while (true)
	{
		while (isReadyToSelect)
		{
			readFdsCopy = readfds;
			writeFdsCopy = writefds;
			if (select(Utils::getMaxFd(clients, this->_socket) + 1, &readFdsCopy, &writeFdsCopy, NULL, 0) < 0)
			{
				throw Exception("Select failed");
			}
			isReadyToSelect = false;
		}
		if (FD_ISSET(this->_socket, &this->readFdsCopy))
		{
			int newSocket = accept(this->_socket, (sockaddr *)&clientAddress, &templen);
			if (newSocket < 0)
			{
				throw Exception("Accept failed");
			}
			if (fcntl(newSocket, F_SETFL, O_NONBLOCK) < 0)
				throw Exception("Fcntl failed on Client");
			int port = ntohs(clientAddress.sin_port);
			Client newClient(newSocket, port);
			char	*ip = inet_ntoa(clientAddress.sin_addr);
			strcpy(newClient._ip, ip);
			clients.push_back(newClient);
			FD_SET(newSocket, &readfds);
			TextEngine::green("New connection from ", TextEngine::printTime(cout)) << newClient._ip << ":" << newClient.getPort() << std::endl;
			isReadyToSelect = true;
			continue;
		}
		for (VECT_ITER_CLI a = clients.begin(); a != clients.end() && !isReadyToSelect; a++)
		{
			if (FD_ISSET(a->getFd(), &this->readFdsCopy))
			{
				bytesRead = read(a->getFd(), this->buffer, 1024);
				if (bytesRead <= 0)
				{
					for (VECT_ITER_CHA it = this->channels.begin(); it != this->channels.end(); it++){
						if (it->isClientInChannel(a->getFd())){
							it->removeClient(a->getFd());
							Utils::instaWriteAll(it->getClients(), RPL_QUIT(a->getUserByHexChat(), "Leaving"));
							responseAllClientResponseToGui(*a, *it);
						}
					}
					FD_CLR(a->getFd(), &readfds);
					FD_CLR(a->getFd(), &writefds);
					close(a->getFd());
					TextEngine::blue("Client ", TextEngine::printTime(cout)) << a->_ip << ":" << a->getPort() << " disconnected" << std::endl;
					clients.erase(a);
					isReadyToSelect = true;
				}
				else
				{
					this->buffer[bytesRead] = '\0';
					string msg = this->buffer;
					if (msg == "\n")
					{
						a->setBuffer(a->getBuffer() + msg);
						isReadyToSelect = true;
					}
					if (msg[msg.length() - 1] != '\n')
					{
						a->setBuffer(a->getBuffer() + msg);
						isReadyToSelect = true;
						break;
					}
					runCommand(a->getBuffer() + msg, *a);
					a->setBuffer("");
					Utils::clearBuffer(this->buffer, 1024);
				}
				isReadyToSelect = true;
				break;
			}
		}
		for (VECT_ITER_CLI a = clients.begin(); a != clients.end() && !isReadyToSelect; ++a)
		{
			if (FD_ISSET(a->getFd(), &this->writeFdsCopy))
			{
				int bytesWritten = write(a->getFd(), a->getmesagesFromServer()[0].c_str(), a->getmesagesFromServer()[0].length());
				a->getmesagesFromServer().erase(a->getmesagesFromServer().begin());
				if (bytesWritten < 0)
				{
					throw Exception("Write failed");
				}
				if (a->getmesagesFromServer().empty()){
					FD_CLR(a->getFd(), &writefds);
				}
				if (bytesWritten == 0)
				{
					for (VECT_ITER_CHA it = this->channels.begin(); it != this->channels.end(); it++){
						if (it->isClientInChannel(a->getFd())){
							it->removeClient(a->getFd());
							Utils::instaWriteAll(it->getClients(), RPL_QUIT(a->getUserByHexChat(), "Leaving"));
							responseAllClientResponseToGui(*a, *it);
						}
					}
					FD_CLR(a->getFd(), &writefds);
					FD_CLR(a->getFd(), &readfds);
					close(a->getFd());
					this->clients.erase(a);
					TextEngine::blue("Client ", TextEngine::printTime(cout)) << a->_ip << ":" << a->getPort() << " disconnected" << std::endl;
				}
				Utils::clearBuffer(this->buffer, 1024);
				isReadyToSelect = true;
				break;
			}
		}
	}
}

void Server::runCommand(C_STR_REF command, Client &client)
{
	TextEngine::underline("----------------\n", cout);
	TextEngine::cyan("Input is : " + command, cout);

	VECT_STR softSplit = Utils::ft_split(command, "\n");
	if (softSplit.size() == 0) return;
	for (size_t i = 0; i < softSplit.size(); i++)
	{
		string trimmedLine = Utils::ft_trim(softSplit[i], " \t\r");
		if (trimmedLine.empty()) return;
		VECT_STR splitFirst = Utils::ft_firstWord(trimmedLine);
		std::map<std::string, void (Server::*)(const string &, Client &)> ::iterator it = this->_commands.find(splitFirst[0]);
		if (it != this->_commands.end())
		{
			(this->*_commands[splitFirst[0]])(splitFirst[1], client);
		}
		else
		{
			Utils::instaWrite(client.getFd(), ERR_UNKNOWNCOMMAND(client.getUserByHexChat(),splitFirst[0]));
		}
	}
}

void Server::responseAllClientResponseToGui(Client &client, Room &room)  {
	string message = "";
	for (VECT_ITER_CLI it = room.getClients().begin(); it != room.getClients().end(); it++){
		if (room.isOperator(*it))
			message += "@";
		message += (*it).getNick() + " ";
	}
	Utils::instaWriteAll(room.getClients(), RPL_NAMREPLY(client.getNick(), room.getName(), message));
	Utils::instaWriteAll(room.getClients(), RPL_ENDOFNAMES(client.getNick(), room.getName()));
}

Client &Server::getClientByNick(C_STR_REF nick){
	VECT_ITER_CLI it = this->clients.begin();
	for (; it != this->clients.end(); ++it)
	{
		if (it->getNick() == nick)
			return *it;
	}
	return *it;
}


Room	&Server::getRoom(C_STR_REF roomName){
	VECT_ITER_CHA it = this->channels.begin();
	for (; it != this->channels.end(); ++it)
	{
		if (it->getName() == roomName)
			return *it;
	}
	return *it;
}

vector<Room> &Server::getRooms(){
	return this->channels;
}

bool	Server::isRoom(C_STR_REF roomName){
	VECT_ITER_CHA it = this->channels.begin();
	for (; it != this->channels.end(); ++it)
	{
		if (it->getName() == roomName)
			return true;
	}
	return false;
}

void	Server::addRoom(const Room &room){
	this->channels.push_back(room);
}

void	Server::addClient(const Client &client){
	this->clients.push_back(client);
}

vector<Client> &Server::getClients(){
	return this->clients;
}

bool	Server::isClientInRoom(Room &room, const Client &client){
	VECT_ITER_CLI it = room.getClients().begin();
	for (; it != room.getClients().end(); ++it)
	{
		if (it->getNick() == client.getNick())
			return true;
	}
	return false;
}

bool	Server::isClientInRoom(Client &client, string &room){
	VECT_ITER_CHA it = this->channels.begin();
	for (; it != this->channels.end(); ++it)
	{
		if (it->getName() == room)
		{
			VECT_ITER_CLI cit = it->getClients().begin();
			for (; cit != it->getClients().end(); ++cit)
			{
				if (cit->getNick() == client.getNick())
					return true;
			}
		}
	}
	return false;
}

bool	Server::isClientInRoom(Room &room, string &nick){
	VECT_ITER_CLI it = room.getClients().begin();
	for (; it != room.getClients().end(); ++it)
	{
		if (it->getNick() == nick)
			return true;
	}
	return false;
}

void	Server::removeClient(int fd){
	VECT_ITER_CLI it = this->clients.begin();
	for (; it != this->clients.end(); ++it)
	{
		if (it->getFd() == fd)
		{
			this->clients.erase(it);
			return;
		}
	}
}


void	Server::initFunctions() {
	this->_commands["PASS"] = &Server::pass;
	this->_commands["pass"] = &Server::pass;
	this->_commands["NICK"] = &Server::nick;
	this->_commands["nick"] = &Server::nick;
	this->_commands["USER"] = &Server::user;
	this->_commands["user"] = &Server::user;
	this->_commands["CAP"] = &Server::cap;
	this->_commands["cap"] = &Server::cap;
	this->_commands["JOIN"] = &Server::join;
	this->_commands["join"] = &Server::join;
	this->_commands["TOPIC"] = &Server::topic;
	this->_commands["topic"] = &Server::topic;
	this->_commands["MODE"] = &Server::mode;
	this->_commands["mode"] = &Server::mode;
	this->_commands["part"] = &Server::part;
	this->_commands["PART"] = &Server::part;
	this->_commands["list"] = &Server::list;
	this->_commands["LIST"] = &Server::list;
	this->_commands["NAMES"] = &Server::names;
	this->_commands["names"] = &Server::names;
	this->_commands["PRIVMSG"] = &Server::privmsg;
	this->_commands["privmsg"] = &Server::privmsg;
	this->_commands["join"] = &Server::join;
	this->_commands["JOIN"] = &Server::join;
	this->_commands["WHOIS"] = &Server::whois;
	this->_commands["whois"] = &Server::whois;
	this->_commands["NOTICE"] = &Server::notice;
	this->_commands["notice"] = &Server::notice;
	this->_commands["QUIT"] = &Server::quit;
	this->_commands["quit"] = &Server::quit;
	this->_commands["KICK"] = &Server::kick;
	this->_commands["kick"] = &Server::kick;
	this->_commands["INVITE"] = &Server::invite;
	this->_commands["invite"] = &Server::invite;
	this->_commands["OP"] = &Server::op;
	this->_commands["op"] = &Server::op;
	this->_commands["WHO"] = &Server::who;
	this->_commands["who"] = &Server::who;
	this->_commands["PING"] = &Server::ping;
	this->_commands["ping"] = &Server::ping;
}
