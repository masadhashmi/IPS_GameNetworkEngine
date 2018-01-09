#include "stdafx.h"
#include "gClient.h"
#include <thread>
#include "ServerListner.h"

std::thread* t1;


gClient::gClient()
{
	_socket = NULL;
	_port = NULL;
}


gClient::~gClient()
{
}

void gClient::setSocket(SOCKET socket)
{
	_socket = socket;
}

 bool gClient::readUserName()
{
	 int recvbuflen = 30;
	 int iResult = 0;
	 char* recvbuf= recvbuf = new char[DEFAULT_BUFLEN];

	 iResult = recv(_socket, recvbuf, recvbuflen, NULL);
	 if (iResult > 0) {
		 int recievelength = iResult;
		 recvbuf[recievelength] = NULL;
		 username = CString(recvbuf);
		 if (username.Trim() == _T(""))
		 {
			 return false;
		 }
		 try { delete(recvbuf); }
		 catch (int er) {}
		 printf("\r\nUser Connected: %ls", username);
		 return true;
	 }
	 else
	 {
		 return false;
	 }
}

bool gClient::operator==(const gClient& rhs) {
	
	bool result = false;
	try {
		result=(this->_port != NULL && rhs._port != NULL && this->_port == rhs._port) ? true : false;//lhs.val == rhs.val && lhs.name == lhs.name;
	}
	catch (int k)
	{
	}

	return result;
}


void gClient::setDelete(deleteClient fnction, void* user)
{
//	OdeleteClient = fnction;
//	context = user;
}

void gClient::startRecieve()
{
	//printf("\r\nStarting Thread.");
	t1=new thread(&gClient::recieveEngine, this);
    t1->detach();
}

void gClient::recieveEngine()
{
	
	int recvbuflen = DEFAULT_BUFLEN;
	int iResult=0;
	char* recvbuf;
	try {
		do {
			diconnectedFrom = "0";
			//printf("\r\nRecieving Data.");
			recvbuf = new char[DEFAULT_BUFLEN];
			iResult = 0;

			try {
				//this->isbussy = true;
				iResult = recv(_socket, recvbuf, recvbuflen, 0);
				if (iResult > 0) {
					int recievelength = iResult;
					recvbuf[recievelength] = NULL;
					CString str = CString(recvbuf);
					printf("\r\nBytes received: %d, %ls", iResult, str);
					try { delete(recvbuf); }
					catch (int er) {
						int kyhu = 0;
					}
					// Echo the buffer back to the sender
					/*int iSendResult = send(_socket, recvbuf, iResult, 0);
					if (iSendResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					//closesocket(ClientSocket);
					//WSACleanup();
					//return ;
					}
					printf("Bytes sent: %d\n", iSendResult);*/
				}
				else if (iResult == 0)
				{
					diconnectedFrom = "1";
					try { delete(recvbuf); }
					catch (int er) {}
					printf("Connection closing...\n");
					try {
						closesocket(_socket);
					}
					catch (int er) {
						int k = 0;
					}
					WSACleanup();
					this->RECIEVE_DATA_FLAG = false;
					this->IS_CONNECTED = false;


					try {
						ServerListner::addDeleteClient(this);
					}
					catch (int er) {}
					//deleteClient obj = (deleteClient)OdeleteClient;

					//obj(this, context);

				}
				else {
					diconnectedFrom = "2";
					try { delete(recvbuf); }
					catch (int er) {}
					diconnectedFrom += "_22";
					printf("recv Failed, Connection closing...\n");
					try {
						diconnectedFrom += "_23";
						closesocket(_socket);
						diconnectedFrom += "_24";
					}
					catch (int er) {}
					diconnectedFrom += "_25";
					WSACleanup();
					this->RECIEVE_DATA_FLAG = false;
					this->IS_CONNECTED = false;
					diconnectedFrom += "_26";
					try {
						diconnectedFrom += "_27";
						ServerListner::addDeleteClient(this);
						diconnectedFrom += "_28";
					}
					catch (int er) {
						diconnectedFrom += "_29";
					}

					//printf("recv failed with error: %d\n", WSAGetLastError());
					//closesocket(_socket);
					//WSACleanup();
					//return ;
				}
			}
			catch (int er)
			{
				diconnectedFrom = "3";
				if (iResult <= 0)
				{
					diconnectedFrom = "4";
					try { delete(recvbuf); }
					catch (int er) {}
					printf("Connection closing...\n");
					try {

						closesocket(_socket);
					}
					catch (int er) {
						int k = 0;
					}
					WSACleanup();
					this->RECIEVE_DATA_FLAG = false;
					this->IS_CONNECTED = false;
					try {
						ServerListner::addDeleteClient(this);
					}
					catch (int er) {}
				}

			}


		} while (RECIEVE_DATA_FLAG);
	}
	catch (int er) {
		diconnectedFrom = "5";
	}
	
	//this->isbussy = false;
}