#include "Client.hpp"
#include <cstring>

Client::Client() :
	_ip("\0"), _fd(-1), _port(-1), isRegistered(false), isPassworded(false) {}

Client::Client(int fd, int port) :
	_fd(fd), _port(port), isRegistered(false), isPassworded(false) {}


Client::Client(const Client &other){
	*this = other;
}

Client &Client::operator=(const Client &other){
	if (this != &other){
		_type = other._type;
		_fd = other._fd;
		_port = other._port;
		buffer = other.buffer;
		_messagesFromServer = other._messagesFromServer;
		isRegistered = other.isRegistered;
		isPassworded = other.isPassworded;
		_nick = other._nick;
		_userName = other._userName;
		_hostName = other._hostName;
		_serverName = other._serverName;
		_realName = other._realName;
		strcpy(_ip, other._ip);
	}
	return *this;
}

int Client::getFd() const {
	return _fd;
}

int Client::getPort() const {
	return _port;
}

string Client::getBuffer() const {
	return buffer;
}

bool Client::getIsRegistered() const {
	return isRegistered;
}

bool Client::getIsPassworded() const {
	return isPassworded;
}

int Client::getType() const {
	return _type;
}

string Client::getNick() const {
	return _nick;
}

string Client::getUserName() const {
	return _userName;
}

string Client::getRealName() const {
	return _realName;
}

string Client::getHostName() const {
	return _hostName;
}

string Client::getServerName() const {
	return _serverName;
}

vector<string> &Client::getmesagesFromServer() {
	return _messagesFromServer;
}

void Client::setNick(C_STR_REF nick) {
	_nick = nick;
}

void Client::setRegistered(bool val) {
	isRegistered = val;
}

void Client::setPassworded(bool val) {
	isPassworded = val;
}

void Client::setBuffer(C_STR_REF str) {
	buffer = str;
}

void Client::setType(int type) {
	_type = type;
}

void Client::setUserName(C_STR_REF userName) {
	_userName = userName;
}

void Client::setRealName(C_STR_REF realName) {
	_realName = realName;
}

void Client::setHostName(C_STR_REF hostName) {
	_hostName = hostName;
}

void Client::setServerName(C_STR_REF serverName) {
	_serverName = serverName;
}

Client::~Client() {}

string Client::getUserByHexChat() const {
	std::string strIP = this->_ip;
	return this->_nick + (this->_userName.empty() ? "" : "!~" + this->_userName) + (strIP.empty() ? "" : "@" + strIP);
}
