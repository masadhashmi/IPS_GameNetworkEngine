#include "stdafx.h"
#include "Client.h"
#include <thread>
#include "SocketListner.h"


using namespace std;



thread* clientThread;


Client::Client()
{

	

}

Client::~Client()
{

}

void Client::setSocket(SubClient* socket)
{
	//_clientsocket = socket;
}

void Client::asyncSelect()
{
	//_clientsocket.AsyncSelect(FD_READ | FD_WRITE | FD_OOB | FD_CONNECT | FD_CLOSE);
}

void Client::fetchDetails()
{
	struct sockaddr_in addr;
	socklen_t addr_size = sizeof(struct sockaddr_in);
	int res = getpeername(this->_client._clientsocket, (struct sockaddr *)&addr, &addr_size);
	char *clientip = new char[15];
	strcpy(clientip, inet_ntoa(addr.sin_addr));

	this->_client.ipaddress.assign(clientip,15);
	this->_client.port = (int)addr.sin_port;
	
}

void Client::display()
{
	printf("\r\nIP:%s:%d", (_client.ipaddress.c_str()), (_client.port));
}

void Client::isClosed()
{
	char* verification = "verification";
	int resp=this->_client._clientsocket.Send(verification,11,0);
	printf("\r\n Verification Resp: %d", resp);
}

void Client::OnReceive(int nErrorCode)
{
	
	printf("data recieved");
	if (nErrorCode == 0)
	{
		try {
			printf("data recieved");
		}
		catch (int er) {}
		//((CEchoServerDlg*)m_pDlg)->OnReceive();
	}

	//_clientsocketCAsyncSocket::OnReceive(nErrorCode);
}

bool Client::operator==(const Client& rhs) {

	
	bool result = false;
	try {
		result = (this->_client.port != NULL && rhs._client.port != NULL && this->_client.port == rhs._client.port) ? true : false;//lhs.val == rhs.val && lhs.name == lhs.name;
	}
	catch (int k)
	{
	}

	return result;
}

void Client::closeClient()
{
	this->_client.RECV_FLAG = false;
	try {
		this->_client._clientsocket.Close();
	}
	catch (int k) {}
	bool isadded = false;
	do {
		try {
			SocketListner::addDeleteClient(this);
			isadded = true;
		}
		catch (int er) {

		}
	} while (!isadded);
}
bool Client::login()
{
	
}
void Client::recv()
{
	/*
	while (this->_client.RECV_FLAG)
	{
		char *pBuf = new char[512];
		try {
			
			CString strData;
			int iLen;
			iLen = this->_client._clientsocket.Receive(pBuf, 512); //_clientsocket.Receive(pBuf, 512);

			if (iLen == 0)
			{
				closeClient();
			}
			else if (iLen == -1)
			{
				//idle state
			}
			else if (iLen>0)
			{
				pBuf[iLen] = NULL;
				strData = pBuf;
				printf("\r\nRecieved : %ls", strData);
			}
			else
			{
				closeClient();
			}
			delete(pBuf);
		}
		catch (int er) { delete(pBuf); }
		Sleep(50);
	}
	*/
}

void Client::start()
{
	clientThread = new thread(&Client::recv, this);
	clientThread->detach();
}