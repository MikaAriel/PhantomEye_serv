#pragma once

// CHKSock ��� ����Դϴ�.

class CPESock : public CAsyncSocket
{
public:
	CPESock();
	virtual ~CPESock();
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


