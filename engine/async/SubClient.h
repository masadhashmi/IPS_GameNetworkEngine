
#if !defined(AFX_MYECHOSOCKET_H__166D4120_2F94_4231_AE60_7C719E3EC05C__INCLUDED_)
#define AFX_MYECHOSOCKET_H__166D4120_2F94_4231_AE60_7C719E3EC05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif // !defined(AFX_MYECHOSOCKET_H__166D4120_2F94_4231_AE60_7C719E3EC05C__INCLUDED_)

#include "afxsock.h" 
class SubClient : public CAsyncSocket
{
public:
	SubClient();
	~SubClient();
	void asyncSelect();

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};

