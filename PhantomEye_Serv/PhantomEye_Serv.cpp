
// PhantomEye_Serv.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
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


// CPhantomEye_ServApp ����

CPhantomEye_ServApp::CPhantomEye_ServApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	m_ServerSock = NULL;
	m_ChildSock = NULL;
	blogSwitch = true;
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CPhantomEye_ServApp ��ü�Դϴ�.

CPhantomEye_ServApp theApp;


// CPhantomEye_ServApp �ʱ�ȭ

BOOL CPhantomEye_ServApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CPhantomEye_ServDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
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
	//MSSQL�ڵ�
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
		//MSSQL�ڵ�
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
	m_pMainWnd->SetDlgItemInt(IDC_COUNT, nCount); // ���� ���ӵ� Ŭ���̾�Ʈ �� ���
}