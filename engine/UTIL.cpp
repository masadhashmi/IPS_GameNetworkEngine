#include "stdafx.h"
#include "UTIL.h"


UTIL::UTIL()
{
}


UTIL::~UTIL()
{
}

char* UTIL::CstringToCharArray(CString value)
{
	char* ipaddressbuffer = new char[value.GetLength()];
	ipaddressbuffer = (char*)LPCSTR(value.GetBuffer(value.GetLength()));
	return ipaddressbuffer;
}
