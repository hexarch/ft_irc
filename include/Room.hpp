#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Client;
#include "Client.hpp"

class Room
{
public:
	Room();
	~Room();
	Room(const Room &other);
	Room &operator=(const Room &other);

	vector<Client>	&getClients() { return _clients; }
	string			getName() const { return _name; }
	string			getTopic() const { return _topic; }
	int				getKeycode() const { return _keycode; }
	string			getKey() const { return _key ; }
	int				getChanelLimit() const { return _chanelLimit; }
	vector<Client>	&getOperatorVector() { return _operatorVector; }
	bool 			isOperator(C_STR_REF nick) const;

	void			addOperator(const Client &client) { _operatorVector.push_back(client); }
	void			removeOperator(const Client &client);
	void			setName(C_STR_REF name) { _name = name; }
	void			setTopic(C_STR_REF topic) { _topic = topic; }
	void			addClient(const Client &client) { _clients.push_back(client); }
	void			setKeycode(int keycode) { _keycode = keycode; }
	void			setKey(C_STR_REF key) { _key = key; }
	void			setChanelLimit(int limit) { _chanelLimit = limit; }
	void			removeClient(int fd);

	bool			isClientInChannel(C_STR_REF nick) const;
	bool			isClientInChannel(int fd) const;
	Client			&getClient(C_STR_REF nick);
	bool			isOperator(const Client &client) const;
	void			addInvite(const Client &client) { _inviteVector.push_back(client); }
	void			removeInvite(const Client &client);
	bool			isInvite(const Client &client) const;
private:
	vector<Client>	_clients;
	string			_name;
	string 			_topic;
	vector<Client>	_operatorVector;
	int				_keycode;
	string			_key;
	int				_chanelLimit;
	vector<Client>	_inviteVector;
};
