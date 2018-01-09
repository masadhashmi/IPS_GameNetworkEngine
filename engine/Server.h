#pragma once
#include "async\SocketListner.h"
#include <list>
#include "async\Client.h"
#include "core\ServerListner.h"
#include "async\SocketListner.h"


class Server
{
	CString _serverip;
	int _port;
	
	SocketListner* _listner;			///---- Non-Blocking
	ServerListner* _serverListner;		///---- Blocking
	
	CDialog* _parrent;
public:
	Server(CString serverip, int port, CDialog* parrent);
	~Server();
	void start(bool isasync);
	void stop(bool isasync);
};

