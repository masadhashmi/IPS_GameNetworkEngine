#include "stdafx.h"
#include "./includes/CoreListner.h"

#include <cstring>
#include <string.h>
#include <atlstr.h>
#include <iostream>
#include "SocketListner.h"
//#include 'StdAfx.h'



using namespace std;
using namespace coreengine;


	CoreListner::CoreListner()
	{
		
	}

	CoreListner::~CoreListner()
	{
	}

	void CoreListner::start(char* _ipaddress, char* _port)
	{
		//long int ss = strtol(_port, NULL, NULL);
		//listner = new SocketListner(1220);
		printf("Connecting with %ls on Port : %ls", _ipaddress, _port);
	}
