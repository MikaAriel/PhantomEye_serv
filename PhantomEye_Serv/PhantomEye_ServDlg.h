
// PhantomEye_ServDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CPhantomEye_ServDlg 대화 상자
class CPhantomEye_ServDlg : public CDialogEx
{
// 생성입니다.
public:
	CPhantomEye_ServDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PHANTOMEYE_SERV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl ConnetList;
	CListCtrl DataList;
	afx_msg void OnBnClickedManyproc();
	afx_msg void OnBnClickedSelfkilling();
	afx_msg void OnBnClickedStartserv();
	afx_msg void OnBnClickedStopserv();
	afx_msg void OnBnClickedViewlog();
	afx_msg void OnBnClickedReboot();
	CButton m_ConStartServ;
	CButton m_StopServ;
	afx_msg void OnBnClickedCalcblock();
	afx_msg void OnBnClickedCalcunblock();
	afx_msg void OnBnClickedFindlog();
	CString m_findcon;
	afx_msg void OnBnClickedShutdown();
	afx_msg void OnBnClickedSendmes();
	CString m_sendmes;
};
