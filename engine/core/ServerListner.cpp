#include "stdafx.h"
#include "ServerListner.h"
#include <thread>
#include "../mainDialog.h"
#include <string>
#include <queue>

std::thread* deleteQThread;
std::thread* t2;
std::thread* socketfdselectthread;


static queue<gClient*> deleteQ;


SOCKET ListenSocket = INVALID_SOCKET;

bool USE_FDSETS = true;
bool FD_SELECT_TASK = true;
fd_set readfds;
struct timeval tv;
int fd_size;

using namespace std;
ServerListner::ServerListner()
{
	if (USE_FDSETS)
	{
		FD_ZERO(&readfds);
	}
}

void ServerListner::addDeleteClient(gClient* cl)
{
	if (cl == NULL)
	{
		int breakthis = 0;
	}
	deleteQ.push(cl);
}

ServerListner::~ServerListner()
{

}

void __stdcall  deleteClient(gClient* client, void* user)
{

	((ServerListner*)user)->deleteClientCB(client);
}

void ServerListner::deleteClientCB(gClient* client)
{
	deleteQ.push(client);
	
}

void ServerListner::Listen()
{
	int iResult;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, SERVER_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return ;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return ;
	}

	// Setup the TCP listening socket
	const sockaddr* name = result->ai_addr;
	iResult=bind(ListenSocket, name, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return ;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return ;
	}
}

SOCKET* ServerListner::Accept()
{
	SOCKET ClientSocket = accept(ListenSocket, NULL, NULL);
	
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return NULL;
	}
	else
	{
		int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed with error: %d\n", iResult);
			return NULL;
		}
	}
	return &ClientSocket;
}

bool ServerListner::isConnected(SOCKET sock)
{
	char buf;
	int err = recv(sock, &buf, 1, MSG_PEEK);
	if (err == SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			return false;
		}
	}
	return true;
}

void ServerListner::serverEngine()
{
	Listen();
	socketlistiterator = ConnectedSocketslist.begin();
	printf("Started accepting the sockets...");
	((mainDialog*)_parrent)->lbl_status.SetWindowTextW(_T("Connected"));
	do {
		//SOCKET* clientSocket = SOCKET();
		gClient* cl = new gClient();
		cl->_socket = *Accept();
		fd_size = cl->_socket + 1;
		if (cl->_socket != NULL)
		{
			if (USE_FDSETS)
			{
				//FD_SET(cl->_socket, &readfds);
			}

			//cl->setIpAddress("");

			socketlistiterator = ConnectedSocketslist.end();
			socketlistiterator++;

			cl->_port=(TotalConnectedSockets);
			cl->setDelete(deleteClient, this);
			//cl->setSocket(*clientSocket);
			cl->IS_CONNECTED = true;
			//cl->startRecieve();
			if (cl->readUserName())
			{
				ConnectedSocketslist[cl->username] = cl;//ConnectedSocketslist.insert(socketlistiterator, cl);
				ConnectedSocketClients[cl->_socket] = cl;
				//ConnectedSocketslist[CurrentIndex] = *cl;

				//CurrentIndex++;

				socketlistiterator++;
				TotalConnectedSockets++;

				update();

				printf("\r\n Sockets: %d", TotalConnectedSockets);
			}
			else
			{
				printf("\r\nclient authentication failed");
			}
		}

	} while (FLAG_ACCEPT);
	((mainDialog*)_parrent)->lbl_status.SetWindowTextW(_T("Disconnected"));
}

void ServerListner::update()
{
	CString totalclients;
	totalclients.Format(_T("%d"), ConnectedSocketslist.size());
	((mainDialog*)_parrent)->lbl_connectedclients.SetWindowTextW(totalclients);
}

void ServerListner::setParrentDlg(CDialog* parrent)
{
	_parrent = parrent;
}

void garbageCollector()
{
	/*while (FLAG_GARBAGE_COLLECTOR)
	{
		try {
			while (deleteQ.size() > 0)
			{
				try {
					gClient* client = deleteQ.front();

					if (client != NULL)
					{
						if (!client->isbussy)
						{
							try {
								deleteQ.pop();
							}
							catch (int er) {}
						}

						CString cport;
						cport.Format(_T("%d"), client->_port);

						try {
							if (!client->isbussy)
							{
								Sleep(2);
								printf("deleting : %ls", cport);
								ConnectedSocketslist.remove(client);
							}
							else
							{
								printf("\r\nclient is busy");
							}
						}
						catch (int er) {

						}
					}
					else
					{
						try {
							deleteQ.pop();
						}
						catch (int er) {}
					}


					update();
				}
				catch (int er) {

					int k = 0;

				}
				Sleep(2);
			}
		}
		catch (int er) {}
		Sleep(500);
	}
	*/
}

void ServerListner::deleteQLoop()
{
	while (FLAG_DELETE_Q)
	{
		try {
			while (deleteQ.size() > 0)
			{
				try {
					gClient* client = deleteQ.front();
					if (client != NULL)
					{
						try {
							deleteQ.pop();
						}catch (int er) {}
						CString cport;
						cport.Format(_T("%d"), client->_port);
						try {
								Sleep(2);
								printf("deleting : %ls", cport);
								ConnectedSocketslist.erase(client->username);//ConnectedSocketslist.remove(client);
						}catch (int er) {}
					}
					else
					{
						try {
							deleteQ.pop();
						}catch (int er) {}
					}
					update();
				}catch (int er) {
					int k = 0;
				}
				Sleep(2);
			}
		}
		catch (int er) {}
		Sleep(500);
	}
}

void ServerListner::start()
{
	t2 = new thread(&ServerListner::serverEngine, this);
	t2->detach();

	deleteQThread = new thread(&ServerListner::deleteQLoop, this);
	deleteQThread->detach();

	if (USE_FDSETS) {
		socketfdselectthread = new thread(&ServerListner::fdSelect, this);
		socketfdselectthread->detach();
	}

}
void ServerListner::getfd_set()
{
	//std::list<gClient*>::iterator it;
	map<CString, gClient*>::iterator it;

	FD_ZERO(&readfds);
	for (it = ConnectedSocketslist.begin(); it != ConnectedSocketslist.end(); it++)
	{
		FD_SET(it->second->_socket, &readfds);
	}
}

void ServerListner::fdSelect()
{
	// wait until either socket has data ready to be recv()d (timeout 10.5 secs)
	tv.tv_sec = 5;
	tv.tv_usec = 500000;
	if (USE_FDSETS) {
		while (FD_SELECT_TASK) {
			int size = fd_size;
			if (size > 0) {
				try {
					getfd_set();
					//fd_set copy = readfds;
					int rv = select(0, &readfds, nullptr, nullptr, &tv);

					if (rv == -1) {
						// error occurred in select()
					}
					else if (rv == 0) {
						printf("Timeout occurred!  No data after 10.5 seconds.\n");
					}
					else {
						try {
							for (int i = 0; i < rv; i++) {
								SOCKET sock = readfds.fd_array[i];
								char* buf = new char[512];
								ZeroMemory(buf, 512);
								int resp = recv(sock, buf, 512, 0);
								if (resp <= 0) {
									printf("\r\n%d=>Socket disconnected.", sock);
									deleteQ.push(ConnectedSocketClients[sock]);
									closesocket(sock);
									FD_CLR(sock, &readfds);
									ConnectedSocketClients.erase(sock);
								}
								else {
									printf("\r\n%d=> Recieved: %s", sock, buf);
									
								}
								delete(buf);
							}
						}
						catch (int e) {}
					}
				}
				catch (int e) {}
			}
			Sleep(20);
		}
	}
}
void ServerListner::stop()
{
	FLAG_ACCEPT = false;
	FLAG_DELETE_Q = false;
}