
// PhantomEye_ServDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

// CPhantomEye_ServDlg ��ȭ ����
class CPhantomEye_ServDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CPhantomEye_ServDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PHANTOMEYE_SERV_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
