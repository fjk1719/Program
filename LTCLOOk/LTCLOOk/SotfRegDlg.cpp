// SotfRegDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LTCLOOk.h"
#include "SotfRegDlg.h"


// CSotfRegDlg 对话框

IMPLEMENT_DYNAMIC(CSotfRegDlg, CDialog)

CSotfRegDlg::CSotfRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSotfRegDlg::IDD, pParent)
{

}

CSotfRegDlg::~CSotfRegDlg()
{
}

void CSotfRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSotfRegDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_WHARDKEY, &CSotfRegDlg::OnBnClickedBtnWhardkey)
	ON_BN_CLICKED(IDC_BTN_CPYID, &CSotfRegDlg::OnBnClickedBtnCpyid)
	ON_BN_CLICKED(IDC_BTN_REG, &CSotfRegDlg::OnBnClickedBtnReg)
END_MESSAGE_MAP()


// CSotfRegDlg 消息处理程序

BOOL CSotfRegDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if(reg.IsRegister())
	{
		AfxMessageBox("软件已经注册");
		OnCancel();

	}
	CString strID= reg.GetHardWareID();
	SetDlgItemText(IDC_EDIT_HardID,strID);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
//取黏贴板数据到输入在窗口
void CSotfRegDlg::OnBnClickedBtnWhardkey()
{
	// TODO: 在此添加控件通知处理程序代码
	if (OpenClipboard())
	{
		if(IsClipboardFormatAvailable(CF_TEXT))
		{
			HANDLE hclip;
			char *pbuff;
			hclip=GetClipboardData(CF_TEXT);
			pbuff=(char*)GlobalLock(hclip);
			GlobalUnlock(hclip);
			CloseClipboard();
			SetDlgItemText(IDC_EDIT_HardKEY,pbuff);
			//AfxMessageBox("");

		}

	}


}

void CSotfRegDlg::OnBnClickedBtnCpyid()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSendMsg;

	if (OpenClipboard())
	{
		GetDlgItemText(IDC_EDIT_HardID,strSendMsg);

		HANDLE hclip;
		char *pbuff;
		EmptyClipboard();
		hclip=GlobalAlloc(GMEM_MOVEABLE,strSendMsg.GetLength()+1);
		pbuff=(char*) GlobalLock(hclip);
		strcpy(pbuff,strSendMsg);
		GlobalUnlock(hclip);
		SetClipboardData(CF_TEXT,hclip);
		CloseClipboard();
		AfxMessageBox("机器码复制成功,请发送给作者QQ:171938416,软件价格:10元");

	}
	
}

void CSotfRegDlg::OnBnClickedBtnReg()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strkey;
	GetDlgItemText(IDC_EDIT_HardKEY,strkey);
	if (strkey.IsEmpty())
	{
		AfxMessageBox("请输入注册码");
		return ;
	}
	reg.WriteHardWareKey(strkey);
	if(AfxMessageBox("写入成功请重新打开软件,验证软件是否注册成功")==1)
	{
		exit(-1);
	}
}
