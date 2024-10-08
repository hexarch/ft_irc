
#include <iostream>
#include "Room.hpp"
#include "Client.hpp"

Room::Room()
	: _clients(), _name(""), _topic(""), _keycode(0),
	  _key(""), _chanelLimit(0)
{
	_clients.reserve(256);
	_operatorVector.reserve(256);
}

Room::~Room() {/* value sementic comes with close errors (select)*/}
Room::Room(const Room &other)
{
	*this = other;
}

Room &Room::operator=(const Room &other)
{
	if (this != &other)
	{
		while (!_clients.empty())
			_clients.pop_back();
		for (size_t i = 0; i < other._clients.size(); i++)
			_clients.push_back(other._clients[i]);
		_name = other._name;
		_topic = other._topic;
		_keycode = other._keycode;
		_key = other._key;
		_chanelLimit = other._chanelLimit;
		_operatorVector = other._operatorVector;
	}
	return *this;
}

void Room::removeClient(int fd)
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].getFd() == fd)
		{
			_clients.erase(_clients.begin() + i);
			break;
		}
	}
}

bool Room::isClientInChannel(C_STR_REF nick) const
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].getNick() == nick)
			return true;
	}
	return false;
}
bool Room::isClientInChannel(int fd) const
{
	for (size_t i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].getFd() == fd)
			return true;
	}
	return false;
}

Client &Room::getClient(C_STR_REF nick)
{
	VECT_ITER_CLI it = _clients.begin();
	for (; it != _clients.end(); ++it)
	{
		if (it->getNick() == nick)
			break;
	}
	return *it;
}

bool Room::isOperator(const Client &client) const
{
	for (size_t i = 0; i < _operatorVector.size(); i++)
	{
		if (_operatorVector[i] == client)
			return true;
	}
	return false;
}

bool Room::isOperator(C_STR_REF nick) const
{
	for (size_t i = 0; i < _operatorVector.size(); i++)
	{
		if (_operatorVector[i].getNick() == nick)
			return true;
	}
	return false;
}

void	Room::removeOperator(const Client &client)
{
	for (vector<Client>::iterator it = _operatorVector.begin(); it != _operatorVector.end(); it++) {
		if (it->getNick() == client.getNick()) {
			_operatorVector.erase(it);
			break;
		}
	}
}

void			Room::removeInvite(const Client &client) {
	for (vector<Client>::iterator it = _inviteVector.begin(); it != _inviteVector.end(); it++) {
		if (it->getNick() == client.getNick()) {
			_inviteVector.erase(it);
			break;
		}
	}
}

bool			Room::isInvite(const Client &client) const{
	for (vector<Client>::const_iterator it = _inviteVector.begin(); it != _inviteVector.end(); it++) {
		if (it->getNick() == client.getNick()) {
			return true;
		}
	}
	return false;

}