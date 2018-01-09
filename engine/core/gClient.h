#pragma once

#define WIN32_LEAN_AND_MEAN

//#include <windows.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <stdlib.h>
//#include <stdio.h>
#include <list>

#define DEFAULT_BUFLEN 99999

// Need to link with Ws2_32.lib
//#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

using namespace std;

class gClient
{
	
	bool RECIEVE_DATA_FLAG = true;
	
	//void* OdeleteClient;
	//void* context;

public:
	SOCKET _socket;
	bool IS_CONNECTED = false;
	bool isbussy = false;
	string _ipaddress="";
	string diconnectedFrom = "-1";
	CString username = _T("");
	int _port=-1;

	gClient();
	~gClient();

	void setSocket(SOCKET socket);

	
	typedef void (CALLBACK *deleteClient)(gClient*, void* user);
	void setDelete(deleteClient fnction, void* user);
	bool operator==( const gClient& rhs);

	bool readUserName();
	void startRecieve();
	void recieveEngine();
};

