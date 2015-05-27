
// PhantomEye_ServDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "PhantomEye_Serv.h"
#include "PhantomEye_ServDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPhantomEye_ServDlg ��ȭ ����




CPhantomEye_ServDlg::CPhantomEye_ServDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPhantomEye_ServDlg::IDD, pParent)
	, m_findcon(_T(""))
	, m_sendmes(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhantomEye_ServDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, ConnetList);
	DDX_Control(pDX, IDC_LIST2, DataList);
	DDX_Control(pDX, IDC_STARTSERV, m_ConStartServ);
	DDX_Control(pDX, IDC_STOPSERV, m_StopServ);
	DDX_Text(pDX, IDC_FIND, m_findcon);
	DDX_Text(pDX, IDC_MES, m_sendmes);
}

BEGIN_MESSAGE_MAP(CPhantomEye_ServDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MANYPROC, &CPhantomEye_ServDlg::OnBnClickedManyproc)
	ON_BN_CLICKED(IDC_SELFKILLING, &CPhantomEye_ServDlg::OnBnClickedSelfkilling)
	ON_BN_CLICKED(IDC_STARTSERV, &CPhantomEye_ServDlg::OnBnClickedStartserv)
	ON_BN_CLICKED(IDC_STOPSERV, &CPhantomEye_ServDlg::OnBnClickedStopserv)
	ON_BN_CLICKED(IDC_VIEWLOG, &CPhantomEye_ServDlg::OnBnClickedViewlog)
	ON_BN_CLICKED(IDC_REBOOT, &CPhantomEye_ServDlg::OnBnClickedReboot)
	ON_BN_CLICKED(IDC_CALCBLOCK, &CPhantomEye_ServDlg::OnBnClickedCalcblock)
	ON_BN_CLICKED(IDC_CALCUNBLOCK, &CPhantomEye_ServDlg::OnBnClickedCalcunblock)
	ON_BN_CLICKED(IDC_FINDLOG, &CPhantomEye_ServDlg::OnBnClickedFindlog)
	ON_BN_CLICKED(IDC_SHUTDOWN, &CPhantomEye_ServDlg::OnBnClickedShutdown)
	ON_BN_CLICKED(IDC_SENDMES, &CPhantomEye_ServDlg::OnBnClickedSendmes)
END_MESSAGE_MAP()


// CPhantomEye_ServDlg �޽��� ó����

BOOL CPhantomEye_ServDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	ConnetList.InsertColumn(0,L"[IP]",LVCFMT_CENTER,170);
	ConnetList.InsertColumn(1,L"[TIME]",LVCFMT_CENTER,80);
	

	DataList.InsertColumn(0,L"[IP]",0,150);
	DataList.InsertColumn(1,L"[TIME]",LVCFMT_CENTER,80);
	DataList.InsertColumn(2,L"[DELAY(ms)]",LVCFMT_CENTER,100);
	DataList.InsertColumn(3,L"[PROCESS]",0,150);
	UpdateData(false);

	m_StopServ.EnableWindow(FALSE);
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CPhantomEye_ServDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CPhantomEye_ServDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CPhantomEye_ServDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPhantomEye_ServDlg::OnBnClickedManyproc()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DataList.DeleteAllItems();
	UpdateData(false);
	while(DataList.GetHeaderCtrl()->GetItemCount() > 0)   
	{
		DataList.DeleteColumn(0);  
	}
	DataList.InsertColumn(0,L"[IP]",LVCFMT_CENTER,170);
	DataList.InsertColumn(1,L"[DELAY]",LVCFMT_CENTER,80);
	DataList.InsertColumn(2,L"[���帹�� ����� ���α׷�]",0,230);
	UpdateData(false);

	CMessageTable<CMessageTableMostValueAccessor> mp;
	if(mp.OpenAll() == S_OK)
	{
		while(mp.MovePrev() == S_OK)
		{
			DataList.InsertItem(0,mp.m_NIP);
			TCHAR ndely[512];
			wsprintf(ndely,L"%ld",mp.m_NDELAY);
			DataList.SetItemText(0,1,ndely);
			DataList.SetItemText(0,2,mp.m_NPROCNAME);
			DataList.UpdateData(false);
		}
	}
}


void CPhantomEye_ServDlg::OnBnClickedSelfkilling()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(SELF_KILLING,L"");
	//((CPhantomEye_ServApp*)AfxGetApp())->SendData(SEND_MES,L"���´�!");
	//((CPhantomEye_ServApp*)AfxGetApp())->SendData(TM_PROGRAM,L"����");
	//((CPhantomEye_ServApp*)AfxGetApp())->SendData(ON_PROGRAM,L"C:\\Program Files\\Adobe\\Adobe Photoshop CS4\\Photoshop.exe");
}


void CPhantomEye_ServDlg::OnBnClickedStartserv()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CPhantomEye_ServApp*)AfxGetApp())->SetListPointer(&ConnetList,&DataList);
	((CPhantomEye_ServApp*)AfxGetApp())->InitServer();
	m_ConStartServ.EnableWindow(FALSE);
	m_StopServ.EnableWindow(TRUE);
}


void CPhantomEye_ServDlg::OnBnClickedStopserv()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CPhantomEye_ServApp*)AfxGetApp())->CleanUp();
	m_ConStartServ.EnableWindow(TRUE);
	m_StopServ.EnableWindow(FALSE);
	ConnetList.DeleteAllItems();
	DataList.DeleteAllItems();
}


void CPhantomEye_ServDlg::OnBnClickedViewlog()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DataList.DeleteAllItems();
	UpdateData(false);
	while(DataList.GetHeaderCtrl()->GetItemCount() > 0)   
	{
		DataList.DeleteColumn(0);  
	}
	DataList.InsertColumn(0,L"[IP]",0,150);
	DataList.InsertColumn(1,L"[TIME]",LVCFMT_CENTER,80);
	DataList.InsertColumn(2,L"[DELAY(ms)]",LVCFMT_CENTER,100);
	DataList.InsertColumn(3,L"[PROCESS]",0,150);
	UpdateData(false);
}



void CPhantomEye_ServDlg::OnBnClickedReboot()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(RE_BOOT,L"");
}


void CPhantomEye_ServDlg::OnBnClickedCalcblock()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(BLOCK_PROGRAM,L"����");
}


void CPhantomEye_ServDlg::OnBnClickedCalcunblock()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(UNBLOCK_PROGRAM,L"����");
}


void CPhantomEye_ServDlg::OnBnClickedFindlog()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	DataList.DeleteAllItems();
	UpdateData(false);

	while(DataList.GetHeaderCtrl()->GetItemCount() > 0)   
	{
		DataList.DeleteColumn(0);  
	}
	DataList.InsertColumn(0,L"[IP]",LVCFMT_CENTER,170);
	DataList.InsertColumn(1,L"[DELAY]",LVCFMT_CENTER,80);
	DataList.InsertColumn(2,L"[�˻� ���α׷�]",0,230);
	UpdateData(false);

	CMessageTable<CMessageTableMostValueAccessor> mp;
	if(mp.OpenAll() == S_OK)
	{
		while(mp.MovePrev() == S_OK)
		{
			if(StrStrW(mp.m_NPROCNAME, m_findcon))
			{
				DataList.InsertItem(0,mp.m_NIP);
				TCHAR ndely[512];
				wsprintf(ndely,L"%ld",mp.m_NDELAY);
				DataList.SetItemText(0,1,ndely);
				DataList.SetItemText(0,2,mp.m_NPROCNAME);
				DataList.UpdateData(false);
			}
			else
				continue;
		}
	}
/*
	CMessageTable<CMessageTableFindValueAccessor> mp;

	lstrcpy(mp.m_NFINDNAME,m_findcon);
	mp.m_dwNFINDNAMELength = lstrlen(m_findcon)*2;
	mp.m_dwNFINDNAMEStatus = DBSTATUS_S_OK;
	
	if(mp.OpenAll() == S_OK)
	{
		while(mp.MoveNext() == S_OK)
		{
			DataList.InsertItem(0,mp.m_NIP);
			TCHAR ndely[512];
			wsprintf(ndely,L"%ld",mp.m_NDELAY);
			DataList.SetItemText(0,1,ndely);
			DataList.SetItemText(0,2,mp.m_NPROCNAME);
			DataList.UpdateData(false);
		}
	}*/


}


void CPhantomEye_ServDlg::OnBnClickedShutdown()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(SHUT_DOWN,L"");
	//((CPhantomEye_ServApp*)AfxGetApp())->SendData(ALLRELEASE_PROGRAM,L"");
}


void CPhantomEye_ServDlg::OnBnClickedSendmes()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	TCHAR temp[512];
	lstrcpy(temp,m_sendmes.GetBuffer());
	m_sendmes.ReleaseBuffer();
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(SEND_MES,temp);
}
