// HKSock.cpp : ���� �����Դϴ�.
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
	((CPhantomEye_ServApp*)AfxGetApp())->ReceiveData(this); // �����͸� �д´�.
	CAsyncSocket::OnReceive(nErrorCode);
}

void CPESock::OnClose(int nErrorCode)
{
	((CPhantomEye_ServApp*)AfxGetApp())->CloseConnect(this);
	CAsyncSocket::OnClose(nErrorCode);
}
// CHKSock ��� �Լ�
