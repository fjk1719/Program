#pragma once
#include "Cooe.h"


// CSotfRegDlg �Ի���

class CSotfRegDlg : public CDialog
{
	DECLARE_DYNAMIC(CSotfRegDlg)

public:
	CSotfRegDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSotfRegDlg();

// �Ի�������
	enum { IDD = IDD_DLG_REGIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CCooe reg;
	

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnWhardkey();
	afx_msg void OnBnClickedBtnCpyid();
	afx_msg void OnBnClickedBtnReg();
};
