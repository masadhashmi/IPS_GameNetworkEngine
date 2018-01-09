// mainDialog.cpp : implementation file
//

#include "stdafx.h"
#include "engine.h"
#include "mainDialog.h"
#include "afxdialogex.h"
#include "UTIL.h"
#include "Server.h"
#include <thread>

#pragma region Varriables

static Server* CurrentServer;
CString ipaddress = _T("");
int _port = 5858;
bool isAsync = false;

std::thread* tmain;
#pragma endregion



IMPLEMENT_DYNAMIC(mainDialog, CDialogEx)

mainDialog::mainDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}


mainDialog::~mainDialog()
{
}

void mainDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_IP, et_ipaddress);
	DDX_Control(pDX, IDC_EDIT_PORT, et_port);
	DDX_Control(pDX, IDC_CHECK2, cb_asyncmode);
	DDX_Control(pDX, IDC_STATIC_ConnectedStatus, lbl_status);
	DDX_Control(pDX, IDC_STATIC_CONNECTEDCLIENTS, lbl_connectedclients);
}


BEGIN_MESSAGE_MAP(mainDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &mainDialog::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &mainDialog::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON1, &mainDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &mainDialog::OnBnClickedButton3)
END_MESSAGE_MAP()

// mainDialog message handlers

void mainDialog::OnBnClickedButton2()
{
	UpdateData(TRUE);
	
	CString port = _T("");
	et_ipaddress.GetWindowTextW(ipaddress);
	et_port.GetWindowTextW(port);
	UINT cbstate=cb_asyncmode.GetState();
	
	int n = -1;
	try {
		 n= _ttoi(port);
	}
	catch (int er) {
		printf("\r\nPort is not correct, Error Code: " + er);
		AfxMessageBox(_T("Please provide valid Port."));
		return;
	}
	if (n <= 0)
	{
		printf("\r\nPort is not correct, Port: %d", n);
		AfxMessageBox(_T("Please provide valid Port."));
		return;
	}

	_port = n;
	
	if (cbstate == BST_CHECKED)
	{
		isAsync = true;
	}

	tmain = new thread(&mainDialog::startServer, this);
	tmain->detach();

}

void mainDialog::startServer()
{
	CurrentServer = new Server(ipaddress,_port,this);
	CurrentServer->start(isAsync);
	
}

void mainDialog::OnBnClickedButtonExit()
{
	this->CloseWindow();
}

void mainDialog::OnBnClickedButton1()
{
	
}

BOOL mainDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	et_port.SetWindowTextW(_T("5858"));

	return TRUE;  
}


void mainDialog::OnBnClickedButton3()
{
	CurrentServer->stop(isAsync);
}
