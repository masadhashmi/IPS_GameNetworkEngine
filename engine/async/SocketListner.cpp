#include "stdafx.h"

#include "SocketListner.h"
//#include "StdAfx.h"
#include "Client.h"
#include <thread>
#include "../mainDialog.h"
#include <queue>
#define synchronized(M)  for(Lock M##_lock = M; M##_lock; M##_lock.setUnlock())


using namespace std;

std::thread* asyncdeleteQThread;
static queue<Client*> deleteQ;




//SocketListner m_sConnected[90000];

CAsyncSocket _ServerSocket;

//CAsyncSocket _socket;
std::thread* async_listner_thread;



SocketListner::SocketListner()
{

}

void SocketListner::addDeleteClient(Client* cl)
{
	if (cl != NULL)
	{
		deleteQ.push(cl);
	}
	
	
}

void SocketListner::setPort(int port)
{
	_port = port;
}



SocketListner::~SocketListner()
{
	//socketlistiterator = ConnectedSocketslist.begin();
}

void SocketListner::setParrentDlg(CDialog* parrent)
{
	_parrent = parrent;
}

void SocketListner::update()
{
	CString totalclients;
	totalclients.Format(_T("%d"), ConnectedSocketslist.size());
	((mainDialog*)_parrent)->lbl_connectedclients.SetWindowTextW(totalclients);
}

void SocketListner::start()
{
	//async_listner_thread = new thread(&SocketListner::serverEngine, this);
	//async_listner_thread->detach();	
	printf("Delete Q attached");
	asyncdeleteQThread = new thread(&SocketListner::deleteQLoop, this);
	asyncdeleteQThread->detach();
}

void SocketListner::stop()
{
	FLAG_DELETE_Q = false;
	FLAG_ACCEPT = false;
}


void SocketListner::serverEngine()
{
	socketlistiterator = ConnectedSocketslist.begin();
	do {
		//SOCKET* clientSocket = SOCKET();
		CAsyncSocket clientsocket;// = new CAsyncSocket;
		
		SOCKADDR clientsocketaddress;
		int clientsocketport;
		try {
			Client* cl = new Client();
			bool res = _ServerSocket.Accept(cl->_client._clientsocket);//cl->_clientsocket);//Accept();
			if (res == true)
			{
				
				cl->fetchDetails();
				try {
					cl->display();
				}
				catch (int er) {}
				cl->asyncSelect();
				ConnectedSocketslist.insert(socketlistiterator, cl);
				
				cl->_client.port = (TotalConnectedSockets);
				cl->_client.RECV_FLAG = true;
				TotalConnectedSockets++;
				//cl->start();
				update();
			}
			else
			{
				//printf("\r\nNothing connected.");
			}
		}
		catch (std::exception& e) {
			printf("\r\nNothing connected. %d", e);
		}
		catch (int ex) {
			printf("\r\nNothing connected. %d", ex);
		}
		Sleep(5);

	} while (FLAG_ACCEPT);
	//((mainDialog*)_parrent)->lbl_status.SetWindowTextW(_T("Disconnected"));
}

bool SocketListner::createAndListen()// onAcceptClient fnction, void* user)
{
	
	//OnAcceptClientCallback=fnction;
	//context = user;

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		/* Tell the user that we could not find a usable */
		/* Winsock DLL.                                  */
		printf("WSAStartup failed with error: %d\n", err);
	}
	_ServerSocket.AsyncSelect(FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE);
	if (!_ServerSocket.Create(_port))
	{
		int lasterror = GetLastError();
		printf("\r\nSocket Creation failed Last Error: %d", lasterror);
		
		return false;
	}
	if (_ServerSocket.Listen() == FALSE)
	{
		printf("\r\nUnable to Listen on that port,please try another port");
		_ServerSocket.Close();
		return false;
	}
	else
	{
		printf("\r\nListening Started....");
		printf("\r\nAccepting a socket");
		((mainDialog*)_parrent)->lbl_status.SetWindowTextW(_T("Connected"));
		//start();
		serverEngine();
		return true;
	}

}

void SocketListner::deleteQLoop()
{
	while (FLAG_DELETE_Q)
	{
		try {

			/*for (gClient* cl : ConnectedSocketslist)
			{
			if (isConnected(cl->_socket))
			{

			printf("%d is Connected", cl->_port);
			}
			else
			{
			printf("%d is isDisconnected", cl->_port);
			}
			}
			Sleep(50);
			*/

			while (deleteQ.size() > 0)
			{
				try {
					Client* client = deleteQ.front();


					if (client != NULL)
					{
						//if (!client->isbussy)
						///	{
						try {
							deleteQ.pop();
						}
						catch (int er) {}
						//}

						CString cport;
						cport.Format(_T("%d"), client->_client.port);

						try {
							//	if (!client->isbussy)
							//		{
							Sleep(2);
							printf("\r\ndeleting : %ls", cport);
							ConnectedSocketslist.remove(client);
							//	}
							//	else
							//	{
							//		printf("\r\nclient is busy");
							//		}
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

}

/*void SocketListner::deleteQLoop()
{
	while (FLAG_DELETE_Q)
	{
		try {

			

			while (deleteQ.size() > 0)
			{
				try {
					Client* client = deleteQ.front();


					if (client != NULL)
					{
						//if (!client->isbussy)
						///	{
						try {
							deleteQ.pop();
						}
						catch (int er) {}
						//}

						CString cport;
						cport.Format(_T("%d"), client->_client.port);

						try {
							//	if (!client->isbussy)
							//		{
							Sleep(2);
							printf("\r\ndeleting : %ls", cport);
							ConnectedSocketslist.remove(client);
							//	}
							//	else
							//	{
							//		printf("\r\nclient is busy");
							//		}
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

}*/

/*
void SocketListner::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{
		printf("A Socket is disconnected");
		//((CEchoServerDlg*)m_pDlg)->OnClose();
	}

	CAsyncSocket::OnClose(nErrorCode);
}

void SocketListner::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{
		
		//((CEchoServerDlg*)m_pDlg)->OnReceive();
	}

	CAsyncSocket::OnReceive(nErrorCode);
}
*/