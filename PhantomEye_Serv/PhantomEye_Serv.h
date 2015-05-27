
// PhantomEye_Serv.h : PROJECT_NAME 응용 프로그램에 대한 주 헤더 파일입니다.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.
#include "PEListen.h"
#include "CPESock.h"

// CPhantomEye_ServApp:
// 이 클래스의 구현에 대해서는 PhantomEye_Serv.cpp을 참조하십시오.
//

class CPhantomEye_ServApp : public CWinApp
{
public:
	CPhantomEye_ServApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

public:
	//네트워크
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
	// 구현입니다.

	DECLARE_MESSAGE_MAP()
};

extern CPhantomEye_ServApp theApp;