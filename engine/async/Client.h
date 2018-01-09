
#if !defined(AFX_MYECHOSOCKET_H__166D4120_2F94_4231_AE60_7C719E3EC05C__INCLUDED_)
#define AFX_MYECHOSOCKET_H__166D4120_2F94_4231_AE60_7C719E3EC05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif // !defined(AFX_MYECHOSOCKET_H__166D4120_2F94_4231_AE60_7C719E3EC05C__INCLUDED_)

#include "afxsock.h" 
#include "SubClient.h"

//#include "StdAfx.h"

struct ClientDetail
{
	std::string ipaddress = "";
	int port = 0;
	std::string username = "";
	std::string connectiontime = "";
	bool connectedstatus = false;
	bool RECV_FLAG = true;
	SubClient _clientsocket;

public:
	void display()
	{
		printf("\r\nIP:%s:%d", ipaddress, port);
	}

};

class Client
{
	
public:
	
	ClientDetail _client;

	Client();
	~Client();

	bool login();
	void asyncSelect();
	void fetchDetails();
	void display();
	void recv();
	void start();
	void isClosed();
	void setSocket(SubClient* socket);
	bool operator==(const Client& rhs);
	void OnReceive(int nErrorCode);

	void closeClient();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
