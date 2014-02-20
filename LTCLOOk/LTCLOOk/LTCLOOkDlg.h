// LTCLOOkDlg.h : 头文件
//

#pragma once
#define WM_ICON_NOTIFY WM_USER+500
//线程声明函数
UINT Gettradesthread(LPVOID lpParam);//成交数据
UINT GetDepththread(LPVOID lpParam);//买卖盘
UINT GetTickerthread(LPVOID lpParam);






// CLTCLOOkDlg 对话框
struct Cticker
{
	CString strbuy;   //买一
	CString strhigh;  //最高价格
	CString strlast;  // 最近成交价格
	CString strlow;  //最低价
	CString strsell; //卖一
	CString strvol; //成交量
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
// 构造
public:
	CLTCLOOkDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LTCLOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	double m_fprice;
	CString m_strMsg;
	BOOL  IsAlert;   //预警开关

	// 生成的消息映射函数
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
	//托盘相关

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
	BOOL  IsWindowXP(); //版本检查是否为windowsxp
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
