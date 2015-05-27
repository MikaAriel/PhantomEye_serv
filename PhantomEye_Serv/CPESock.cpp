// HKSock.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PhantomEye_Serv.h"
#include "CPESock.h"


// CHKSock

CPESock::CPESock()
{
}

CPESock::~CPESock()
{
}

void CPESock::OnReceive(int nErrorCode)
{
	((CPhantomEye_ServApp*)AfxGetApp())->ReceiveData(this); // 데이터를 읽는다.
	CAsyncSocket::OnReceive(nErrorCode);
}

void CPESock::OnClose(int nErrorCode)
{
	((CPhantomEye_ServApp*)AfxGetApp())->CloseConnect(this);
	CAsyncSocket::OnClose(nErrorCode);
}
// CHKSock 멤버 함수
