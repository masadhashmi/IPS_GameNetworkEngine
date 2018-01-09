#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <map>
#include "gClient.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
using namespace std;
class ServerListner
{
	//std::list<gClient*> ConnectedSocketslist;
	//std::list<gClient*>::iterator socketlistiterator;

	map<CString, gClient*> ConnectedSocketslist;
	map<CString, gClient*>::iterator socketlistiterator;

	map<int, gClient*> ConnectedSocketClients;

	bool lock = false;
	//gClient ConnectedSocketslist[90000];
	//int CurrentIndex = 0;

	//SOCKET ClientSocket = INVALID_SOCKET;
	
	int TotalConnectedSockets = 0;
	bool FLAG_ACCEPT = true;
	bool FLAG_DELETE_Q = true;
	bool FLAG_GARBAGE_COLLECTOR = true;

	WSADATA wsaData;

	CDialog* _parrent;

public:



	PCSTR SERVER_PORT="5858";

	ServerListner();
	~ServerListner();

	void setParrentDlg(CDialog* parrent);
	bool isConnected(SOCKET sock);

	void deleteClientCB(gClient* client);
	static void addDeleteClient(gClient* cl);

	void update();

	void Listen();
	SOCKET* Accept();


	void getfd_set();
	void deleteQLoop();
	void fdSelect();
	void garbageCollector();

	void start();
	void stop();
	void serverEngine();
};

