#pragma once

// CPEListen 명령 대상입니다.

class CPEListen : public CAsyncSocket
{
public:
	CPEListen();
	virtual ~CPEListen();
public:
	virtual void OnAccept(int nErrorCode);
};


