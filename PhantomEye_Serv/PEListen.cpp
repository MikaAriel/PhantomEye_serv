// PEListen.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PhantomEye_Serv.h"
#include "PEListen.h"


// CPEListen

CPEListen::CPEListen()
{
}

CPEListen::~CPEListen()
{
}


// CPEListen 멤버 함수
void CPEListen::OnAccept(int nErrorCode)
{
	((CPhantomEye_ServApp*)AfxGetApp())->Accept(); // 접속 허용을 위해 호출
	CAsyncSocket::OnAccept(nErrorCode);
}