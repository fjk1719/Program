#pragma once
#include "Cooe.h"


// CSotfRegDlg 对话框

class CSotfRegDlg : public CDialog
{
	DECLARE_DYNAMIC(CSotfRegDlg)

public:
	CSotfRegDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSotfRegDlg();

// 对话框数据
	enum { IDD = IDD_DLG_REGIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CCooe reg;
	

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnWhardkey();
	afx_msg void OnBnClickedBtnCpyid();
	afx_msg void OnBnClickedBtnReg();
};
