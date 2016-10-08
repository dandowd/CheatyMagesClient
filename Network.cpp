#include "stdafx.h"
#include "Network.h"

#pragma comment (lib, "Ws2_32.lib")

#define UNICODE
#define BUFLEN 512
#define PORT 27015

Network::Network(std::string ip)
{
	CreateSocket(ip);
}

Network::~Network()
{
	CloseSocket(_socket);
}

std::wstring convertToWideStr(std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

	void Network::CreateSocket(std::string ip) {
	int slen = sizeof(_server), playerCount = 0;
	char buf[BUFLEN];
	std::wstring stemp = convertToWideStr(ip);
	LPCWSTR serverIP = stemp.c_str();
	WSADATA wsa;

	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//create socket
	if ((_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char *)&_server, 0, sizeof(_server));
	_server.sin_family = AF_INET;
	_server.sin_port = htons(PORT);
	InetPton(AF_INET, serverIP, &(_server.sin_addr.S_un.S_addr));
}

int Network::CloseSocket(SOCKET socket) {
	closesocket(socket);
	WSACleanup();

	return 0;
}

int Network::Send(std::string message) {
	const char *cstr = message.c_str();

	int slen = sizeof(_server);

	int result = sendto(_socket, cstr, strlen(cstr), 0, (struct sockaddr *)&_server, slen);

	if (result == SOCKET_ERROR) {
		printf("Socket Error %d\n", WSAGetLastError());
	}

	printf("Bytes Sent: %ld\n", result);

	return result;
}

std::string Network::Receive() {
	char buf[BUFLEN];
	sockaddr_in si;
	int recv_len;
	int slen;

	recv_len = recvfrom(_socket, buf, BUFLEN, 0, (struct sockaddr*)&si, &slen);
	buf[recv_len] = '\0';

	return std::string(buf);
}