#pragma once

#ifndef NETWORK_H
#define NETWORK_H

#include "stdafx.h"

class Network
{
public:
	Network(std::string ip);
	~Network();

	int Network::Send(std::string);
	std::string Network::Receive();


private:
	void Network::CreateSocket(std::string);
	int Network::CloseSocket(SOCKET);
	SOCKET _socket;
	struct sockaddr_in _server;
};

#endif