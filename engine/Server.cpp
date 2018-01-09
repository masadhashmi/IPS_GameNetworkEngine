#include "stdafx.h"
#include "Server.h"
#include "async\SocketListner.h"
#include "mainDialog.h"
#include "async\Client.h"

Server::Server(CString serverip, int port, CDialog* parrent)
{
	_serverip = serverip;
	_port = port;
	_parrent = parrent;
}

void Server::start(bool isasync)
{
	if (isasync)
	{
		printf("\r\nStarting Server %ls on port %d", _serverip, _port);
		_listner = new SocketListner();
		_listner->setPort(_port);
		_listner->setParrentDlg(_parrent);
		_listner->start();
		_listner->createAndListen();// onAcceptClient, this);
	}
	else
	{
		_serverListner = new ServerListner();
		_serverListner->setParrentDlg(_parrent);
		_serverListner->start();
	}
	
}

void Server::stop(bool isasync)
{
	if (isasync)
	{
		printf("\r\nStoping Server(Async) %ls on port %d", _serverip, _port);
		_listner->stop();
	}
	else
	{
		printf("\r\nStoping Server(Normal) %ls on port %d", _serverip, _port);
		_serverListner->stop();
	}
}

Server::~Server()
{

}
