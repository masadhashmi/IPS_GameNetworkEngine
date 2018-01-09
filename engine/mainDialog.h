#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// mainDialog dialog

class mainDialog : public CDialogEx
{
	DECLARE_DYNAMIC(mainDialog)

public:

	mainDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~mainDialog();
	//static Server* getServerObject();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	void startServer();
	afx_msg void OnBnClickedButton2();
	CIPAddressCtrl et_ipaddress;
	CEdit et_port;
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	CButton cb_asyncmode;
	CStatic lbl_status;
	CStatic lbl_connectedclients;
	afx_msg void OnBnClickedButton3();
};
