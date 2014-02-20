// SetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LTCLOOk.h"
#include "SetDlg.h"


// CSetDlg 对话框

IMPLEMENT_DYNAMIC(CSetDlg, CDialog)

CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
{

}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
END_MESSAGE_MAP()


// CSetDlg 消息处理程序
