#pragma once

// CPEListen ��� ����Դϴ�.

class CPEListen : public CAsyncSocket
{
public:
	CPEListen();
	virtual ~CPEListen();
public:
	virtual void OnAccept(int nErrorCode);
};


