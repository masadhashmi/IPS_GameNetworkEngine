#include "stdafx.h"
#include "SubClient.h"


SubClient::SubClient()
{
}


SubClient::~SubClient()
{
}

void SubClient::asyncSelect()
{
	AsyncSelect(FD_READ | FD_WRITE | FD_OOB | FD_CONNECT | FD_CLOSE);
}

void SubClient::OnReceive(int nErrorCode)
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

	SubClient::OnReceive(nErrorCode);
}

void SubClient::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if (nErrorCode == 0)
	{
		printf("\r\n Socket delted");
	}


	CAsyncSocket::OnClose(nErrorCode);
}