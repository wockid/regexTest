
// regexTestDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CregexTestDlg dialog
class CregexTestDlg : public CDialog
{
// Construction
public:
	CregexTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_REGEXTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	void SetDefault();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedGetAll();
	CEdit m_ctlEditSource;
	CEdit m_editREGEX1;
	CEdit m_editREGEX2;
	CListBox m_listResults;
	afx_msg void OnBnClickedBtnGetAll2();
};
