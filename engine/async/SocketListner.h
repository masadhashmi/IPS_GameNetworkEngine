#pragma once

#include "afxsock.h" 

#include "Client.h"
#include <list>


#define synchronized(M)  for(Lock M##_lock = M; M##_lock; M##_lock.setUnlock())

class SocketListner 
{
	int _port;
	int TotalClients=0;
	void* OnAcceptClientCallback;
	void* context;
	
	//std::vector<CAsyncSocket> ConnectedSocketslist;
	int CurrentInsertIndex = 0;
	//std::vector<Client>::iterator socketlistiterator;
public:

	std:: list<Client*> ConnectedSocketslist;
	std:: list<Client*>::iterator socketlistiterator;
	
	 //static const std:: list<Client*> mylist;
	bool FLAG_ACCEPT = true;
	CDialog* _parrent;
	bool FLAG_DELETE_Q = true;
	int TotalConnectedSockets = 0;

	SocketListner();
	virtual ~SocketListner();

	void start();
	void stop();
	void serverEngine();
	void deleteQLoop();
	static void addDeleteClient(Client* cl);

	void setParrentDlg(CDialog* parrent);
	void update();
	void setPort(int port);
	bool createAndListen();
	

};

