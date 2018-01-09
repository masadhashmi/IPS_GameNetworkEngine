// engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "engine.h"
#include "mainDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

void load()
{
	mainDialog* mdlg;
	mdlg = new mainDialog();
	mdlg->DoModal();
}

int main()
{
    int nRetCode = 0;
	load();

    return nRetCode;
}
