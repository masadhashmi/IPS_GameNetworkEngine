#pragma once

#include <cstring>
#include "string.h"
#include <atlstr.h>
#include <iostream>
#include "SocketListner.h"
//#include 'StdAfx.h'

#ifdef COREENGINE_EXPORTS  
#define COREENGINE_API __declspec(dllexport)   
#else  
#define COREENGINE_API __declspec(dllimport)   
#endif  

#define  API_CALL	WINAPI

using namespace std;

namespace coreengine
{
	class CoreListner
	{
		SocketListner listner;

	public:
		
		 COREENGINE_API CoreListner();
		 COREENGINE_API ~CoreListner();

		 COREENGINE_API void API_CALL start(char* _ipaddress, char* _port);
		 
	};
}