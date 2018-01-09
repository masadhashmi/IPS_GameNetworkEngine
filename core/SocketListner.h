#pragma once

#include "afxsock.h" 
#include "StdAfx.h"

#if !defined(AFX_MYECHOSOCKET_H__166D4120_2F94_4231_AE60_7C719E3EC05C__INCLUDED_)
#define AFX_MYECHOSOCKET_H__166D4120_2F94_4231_AE60_7C719E3EC05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class SocketListner : public CAsyncSocket
{
	int _port;
public:
	SocketListner();
	SocketListner(int port);
	~SocketListner();
	bool createAndListen();
};

#endif //