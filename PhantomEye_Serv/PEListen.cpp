// PEListen.cpp : ���� �����Դϴ�.
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


// CPEListen ��� �Լ�
void CPEListen::OnAccept(int nErrorCode)
{
	((CPhantomEye_ServApp*)AfxGetApp())->Accept(); // ���� ����� ���� ȣ��
	CAsyncSocket::OnAccept(nErrorCode);
}