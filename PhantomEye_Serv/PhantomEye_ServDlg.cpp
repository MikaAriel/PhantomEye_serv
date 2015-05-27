
// PhantomEye_ServDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "PhantomEye_Serv.h"
#include "PhantomEye_ServDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CPhantomEye_ServDlg 대화 상자




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


// CPhantomEye_ServDlg 메시지 처리기

BOOL CPhantomEye_ServDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	ConnetList.InsertColumn(0,L"[IP]",LVCFMT_CENTER,170);
	ConnetList.InsertColumn(1,L"[TIME]",LVCFMT_CENTER,80);
	

	DataList.InsertColumn(0,L"[IP]",0,150);
	DataList.InsertColumn(1,L"[TIME]",LVCFMT_CENTER,80);
	DataList.InsertColumn(2,L"[DELAY(ms)]",LVCFMT_CENTER,100);
	DataList.InsertColumn(3,L"[PROCESS]",0,150);
	UpdateData(false);

	m_StopServ.EnableWindow(FALSE);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPhantomEye_ServDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPhantomEye_ServDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPhantomEye_ServDlg::OnBnClickedManyproc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DataList.DeleteAllItems();
	UpdateData(false);
	while(DataList.GetHeaderCtrl()->GetItemCount() > 0)   
	{
		DataList.DeleteColumn(0);  
	}
	DataList.InsertColumn(0,L"[IP]",LVCFMT_CENTER,170);
	DataList.InsertColumn(1,L"[DELAY]",LVCFMT_CENTER,80);
	DataList.InsertColumn(2,L"[가장많이 사용한 프로그램]",0,230);
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(SELF_KILLING,L"");
	//((CPhantomEye_ServApp*)AfxGetApp())->SendData(SEND_MES,L"나온다!");
	//((CPhantomEye_ServApp*)AfxGetApp())->SendData(TM_PROGRAM,L"계산기");
	//((CPhantomEye_ServApp*)AfxGetApp())->SendData(ON_PROGRAM,L"C:\\Program Files\\Adobe\\Adobe Photoshop CS4\\Photoshop.exe");
}


void CPhantomEye_ServDlg::OnBnClickedStartserv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CPhantomEye_ServApp*)AfxGetApp())->SetListPointer(&ConnetList,&DataList);
	((CPhantomEye_ServApp*)AfxGetApp())->InitServer();
	m_ConStartServ.EnableWindow(FALSE);
	m_StopServ.EnableWindow(TRUE);
}


void CPhantomEye_ServDlg::OnBnClickedStopserv()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CPhantomEye_ServApp*)AfxGetApp())->CleanUp();
	m_ConStartServ.EnableWindow(TRUE);
	m_StopServ.EnableWindow(FALSE);
	ConnetList.DeleteAllItems();
	DataList.DeleteAllItems();
}


void CPhantomEye_ServDlg::OnBnClickedViewlog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(RE_BOOT,L"");
}


void CPhantomEye_ServDlg::OnBnClickedCalcblock()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(BLOCK_PROGRAM,L"계산기");
}


void CPhantomEye_ServDlg::OnBnClickedCalcunblock()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(UNBLOCK_PROGRAM,L"계산기");
}


void CPhantomEye_ServDlg::OnBnClickedFindlog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	DataList.DeleteAllItems();
	UpdateData(false);

	while(DataList.GetHeaderCtrl()->GetItemCount() > 0)   
	{
		DataList.DeleteColumn(0);  
	}
	DataList.InsertColumn(0,L"[IP]",LVCFMT_CENTER,170);
	DataList.InsertColumn(1,L"[DELAY]",LVCFMT_CENTER,80);
	DataList.InsertColumn(2,L"[검색 프로그램]",0,230);
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(SHUT_DOWN,L"");
	//((CPhantomEye_ServApp*)AfxGetApp())->SendData(ALLRELEASE_PROGRAM,L"");
}


void CPhantomEye_ServDlg::OnBnClickedSendmes()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	TCHAR temp[512];
	lstrcpy(temp,m_sendmes.GetBuffer());
	m_sendmes.ReleaseBuffer();
	((CPhantomEye_ServApp*)AfxGetApp())->SendData(SEND_MES,temp);
}
