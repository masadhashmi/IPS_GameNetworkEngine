#include "stdafx.h"
#include "SocketListner.h"
#include "StdAfx.h"

SocketListner::SocketListner(int port)
{
	_port = port;
}

SocketListner::SocketListner()
{
}

SocketListner::~SocketListner()
{
}

bool SocketListner::createAndListen()
{
	Create(_port);
	if (Listen() == FALSE)
	{
		printf("Unable to Listen on that port,please try another port");
		Close();
		return false;
	}
	else
	{
		printf("Listening Started....");
		return true;
	}
}