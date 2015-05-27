#pragma once

// CHKSock 명령 대상입니다.

class CPESock : public CAsyncSocket
{
public:
	CPESock();
	virtual ~CPESock();
public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


