// NewCheatyClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Network.h"
#include <iostream>

using namespace std;

int main()
{
	string test = "";
	cout << "Enter IP of server: ";
	cin >> test;
	Network net(test);
	cout << "Enter message for server: ";
	cin >> test;
	net.Send(test);
    return 0;
}

