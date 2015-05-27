
// PhantomEye_Serv.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "PEListen.h"
#include "CPESock.h"

// CPhantomEye_ServApp:
// �� Ŭ������ ������ ���ؼ��� PhantomEye_Serv.cpp�� �����Ͻʽÿ�.
//

class CPhantomEye_ServApp : public CWinApp
{
public:
	CPhantomEye_ServApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

public:
	//��Ʈ��ũ
	void SetListPointer(CListCtrl* plcon,CListCtrl* plog);
	void InitServer();
	void CleanUp();

	void SendData(UINT type,TCHAR* info);
	void ReceiveData(CPESock* pRecSock);
	void Accept();
	void CloseConnect(CPESock* pCloSock);

	CListCtrl* plConnect,*pllog;
	bool blogSwitch;
	CPEListen* m_ServerSock;
	CPESock* m_ChildSock;
	CObList m_SockList;
public:
	//MSSQL
	// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPhantomEye_ServApp theApp;