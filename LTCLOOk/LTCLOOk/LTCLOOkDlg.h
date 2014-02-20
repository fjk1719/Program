// LTCLOOkDlg.h : ͷ�ļ�
//

#pragma once
#define WM_ICON_NOTIFY WM_USER+500
//�߳���������
UINT Gettradesthread(LPVOID lpParam);//�ɽ�����
UINT GetDepththread(LPVOID lpParam);//������
UINT GetTickerthread(LPVOID lpParam);






// CLTCLOOkDlg �Ի���
struct Cticker
{
	CString strbuy;   //��һ
	CString strhigh;  //��߼۸�
	CString strlast;  // ����ɽ��۸�
	CString strlow;  //��ͼ�
	CString strsell; //��һ
	CString strvol; //�ɽ���
	 Cticker()
	{
		strbuy="";
		strhigh="";
		strlast="";
		strlow="";
		strsell="";
		strvol="";
	}
};
struct CTrades
{
	CString stramount;
	CString strdata;
	CString strprice;
	CString strtid;
	CString strtype;
	CTrades()
	{
		stramount="";
		strdata="";
		strprice="";
		strtid="";
		strtype="";

	}


};
class CLTCLOOkDlg : public CDialog
{
// ����
public:
	CLTCLOOkDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LTCLOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	double m_fprice;
	CString m_strMsg;
	BOOL  IsAlert;   //Ԥ������

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT OnTrayNotify(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	bool GetDataApi(CString strURL,CString *strReturn);
	afx_msg void OnBnClickedButton1();
	Cticker m_ticker;
	void GetTicker();
	void GetDepth();
	//�������

	BOOL CLTCLOOkDlg::SetupTrayIcon(HWND hwnd);
	BOOL RemoveTrayIcon();
	BOOL CloseToolTip();
	BOOL cltShowToolTip(LPCTSTR szMsg,LPCTSTR szTitle,DWORD dwInfoFlags,UINT uTimeout);
		

	CString StrUrl;

	CString m_edit_last;
	CTrades m_trades;
	float m_high;
	float m_low;
	bool  ishighalert;
	bool  islowalert;
	BOOL  IsWindowXP(); //�汾����Ƿ�Ϊwindowsxp
	BOOL m_b_WindowXP;

	afx_msg void OnBnClickedButton2();
	BOOL CLTCLOOkDlg::OpenMedia(CString lpszName);
	void CLTCLOOkDlg::PriceAlert();
	BOOL isfree();
	//RGB rgb(255,255,255);
	 NOTIFYICONDATA m_tnd;

	

	afx_msg void OnBnClickedBtnGetmsg();
	afx_msg void OnAbout();
	afx_msg void OnDlgRegbox();
//	afx_msg UINT OnNotifyFormat(CWnd *pWnd, UINT nCommand);
protected:
	virtual void OnCancel();
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMAlert();
};
