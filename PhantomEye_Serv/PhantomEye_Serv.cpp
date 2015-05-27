
// PhantomEye_Serv.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
//

#include "stdafx.h"
#include "PhantomEye_Serv.h"
#include "PhantomEye_ServDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPhantomEye_ServApp

BEGIN_MESSAGE_MAP(CPhantomEye_ServApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CPhantomEye_ServApp 생성

CPhantomEye_ServApp::CPhantomEye_ServApp()
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	m_ServerSock = NULL;
	m_ChildSock = NULL;
	blogSwitch = true;
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CPhantomEye_ServApp 개체입니다.

CPhantomEye_ServApp theApp;


// CPhantomEye_ServApp 초기화

BOOL CPhantomEye_ServApp::InitInstance()
{
	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다.
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록
	// 이 항목을 설정하십시오.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// 대화 상자에 셸 트리 뷰 또는
	// 셸 목록 뷰 컨트롤이 포함되어 있는 경우 셸 관리자를 만듭니다.
	CShellManager *pShellManager = new CShellManager;

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));

	CPhantomEye_ServDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고  응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}
void CPhantomEye_ServApp::SetListPointer(CListCtrl* plcon,CListCtrl* plog)
{
	plConnect = plcon;
	pllog = plog;
}
void CPhantomEye_ServApp::InitServer()
{
	m_ServerSock = new CPEListen;
	m_ServerSock->Create(2222);
	m_ServerSock->Listen();
}
void CPhantomEye_ServApp::CleanUp()
{
	CPESock* pSock;
	while(!m_SockList.IsEmpty())
	{
		pSock = (CPESock*)m_SockList.RemoveHead();
		delete pSock;
	}

	if(m_ServerSock)
	{
		delete m_ServerSock;
	}
}

void CPhantomEye_ServApp::SendData(UINT type,TCHAR* info)
{
	CString ip;
	UINT temp;
	CommandMes pmes;
	pmes.mtype = type;
	lstrcpy(pmes.minfo,info);
	CPESock* pSock;
	POSITION pos = m_SockList.GetHeadPosition();
	plConnect->UpdateData(TRUE);
	POSITION lpos = plConnect->GetFirstSelectedItemPosition();
	int FindIP = 0;

	if(lpos == NULL)
	{
		while(pos != NULL)
		{
			pSock = (CPESock*)m_SockList.GetAt(pos);
			pSock->Send(&pmes,sizeof(pmes));
			m_SockList.GetNext(pos);
		}
	}
	else
	{
		while(pos != NULL)
		{
			pSock = (CPESock*)m_SockList.GetAt(pos);
			pSock->GetPeerName(ip,temp);
			FindIP = plConnect->GetNextSelectedItem(lpos);
			if(!ip.Compare(plConnect->GetItemText(FindIP,0)))
			{
				pSock->Send(&pmes,sizeof(pmes));
			}
			m_SockList.GetNext(pos);
		}
	}
}
void CPhantomEye_ServApp::ReceiveData(CPESock* pRecSock)
{
	Mesinfo ms;
	pRecSock->Receive(&ms,sizeof(ms));
	if(blogSwitch)
	{
		CString dtime;
		_wstrtime((TCHAR*)dtime.GetString());
		pllog->InsertItem(0,ms.mip);
		pllog->SetItemText(0,1,dtime);
		wsprintf((LPWSTR)dtime.GetString(),L"%d",ms.mdelay);
		pllog->SetItemText(0,2,dtime);
		pllog->SetItemText(0,3,ms.mprocname);
		pllog->UpdateData(false);
	}
	//MSSQL코드
	CMessageTable<CMessageTableInsertAccessor> DBConnect;
	TCHAR ttime[17];
	_wstrtime(ttime);
	lstrcpy(DBConnect.m_NTIME,ttime);
	DBConnect.m_dwNTIMELength = lstrlen(ttime)*2;
	DBConnect.m_dwNTIMEStatus = DBSTATUS_S_OK;

	lstrcpy(DBConnect.m_NIP,ms.mip);
	DBConnect.m_dwNIPLength = lstrlen(ms.mip)*2;
	DBConnect.m_dwNIPStatus = DBSTATUS_S_OK;

	DBConnect.m_NPORT = ms.mport;
	DBConnect.m_dwNPORTLength = sizeof(ms.mport);
	DBConnect.m_dwNPORTStatus = DBSTATUS_S_OK;

	DBConnect.m_NDELAY = ms.mdelay;
	DBConnect.m_dwNDELAYLength = sizeof(ms.mdelay);
	DBConnect.m_dwNDELAYStatus = DBSTATUS_S_OK;

	lstrcpy(DBConnect.m_NPROCNAME,ms.mprocname);
	DBConnect.m_dwNPROCNAMELength = lstrlen(ms.mprocname)*2;
	DBConnect.m_dwNPROCNAMEStatus = DBSTATUS_S_OK;

	DBConnect.OpenAll();
	/*if(DBConnect.OpenAll() == S_OK)
	{
		if(DBConnect.MoveNext() == S_OK)
		{

		}
	}*/

	//
}
void CPhantomEye_ServApp::Accept()
{
	CString addr;
	UINT port;
	CPESock* pSock = new CPESock;
	if(!m_ServerSock->Accept(*pSock))
	{
		//MSSQL코드
		return;
	}
	m_SockList.AddTail(pSock);

	pSock->GetPeerName(addr,port);
	CString dtime;
	_wstrtime((TCHAR*)dtime.GetString());
	
	plConnect->InsertItem(0,addr);
	plConnect->SetItemText(0,1,dtime);
	plConnect->UpdateData(false);

	int nCount = m_SockList.GetCount();
	m_pMainWnd->SetDlgItemInt(IDC_COUNT,nCount);
}
void CPhantomEye_ServApp::CloseConnect(CPESock* pCloSock)
{
	CPESock* pSock;
	POSITION pos = m_SockList.GetHeadPosition();								
	while( pos !=NULL)
	{
		pSock = (CPESock*)m_SockList.GetAt(pos);
		if(pSock == pCloSock) 
		{
			LVFINDINFO find_item;
			find_item.flags = LVFI_STRING;
			CString addr;
			UINT temp;
			pSock->GetPeerName(addr,temp);
			find_item.psz = addr;

			int index = plConnect->FindItem(&find_item);
			if(-1 != index) plConnect->DeleteItem(index);
			plConnect->UpdateData();
			m_SockList.RemoveAt(pos);
			delete pSock;
			break;
		}
		m_SockList.GetNext(pos);
	}
	int nCount = m_SockList.GetCount(); 
	m_pMainWnd->SetDlgItemInt(IDC_COUNT, nCount); // 현재 접속된 클라이언트 수 출력
}