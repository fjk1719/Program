// SotfRegDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LTCLOOk.h"
#include "SotfRegDlg.h"


// CSotfRegDlg �Ի���

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


// CSotfRegDlg ��Ϣ�������

BOOL CSotfRegDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(reg.IsRegister())
	{
		AfxMessageBox("����Ѿ�ע��");
		OnCancel();

	}
	CString strID= reg.GetHardWareID();
	SetDlgItemText(IDC_EDIT_HardID,strID);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
//ȡ��������ݵ������ڴ���
void CSotfRegDlg::OnBnClickedBtnWhardkey()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		AfxMessageBox("�����븴�Ƴɹ�,�뷢�͸�����QQ:171938416,����۸�:10Ԫ");

	}
	
}

void CSotfRegDlg::OnBnClickedBtnReg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strkey;
	GetDlgItemText(IDC_EDIT_HardKEY,strkey);
	if (strkey.IsEmpty())
	{
		AfxMessageBox("������ע����");
		return ;
	}
	reg.WriteHardWareKey(strkey);
	if(AfxMessageBox("д��ɹ������´����,��֤����Ƿ�ע��ɹ�")==1)
	{
		exit(-1);
	}
}
