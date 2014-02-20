// LTCLOOkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LTCLOOk.h"
#include "LTCLOOkDlg.h"
#include "Cooe.h"
#include "SotfRegDlg.h"
#include <Mmsystem.h>
#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
BOOL IsfreeDC=TRUE;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
CCooe reg;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAbout();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_COMMAND(ID_ABOUT, &CAboutDlg::OnAbout)
END_MESSAGE_MAP()


// CLTCLOOkDlg 对话框




CLTCLOOkDlg::CLTCLOOkDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLTCLOOkDlg::IDD, pParent)
	, m_edit_last(_T(""))
	, m_high(0)
	, m_low(0)
	,ishighalert(FALSE)
	,islowalert(FALSE)
	,IsAlert(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLTCLOOkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LAST, m_edit_last);
	DDX_Text(pDX, IDC_EDIT2, m_high);
	DDX_Text(pDX, IDC_EDIT3, m_low);
}

BEGIN_MESSAGE_MAP(CLTCLOOkDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CLTCLOOkDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLTCLOOkDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BTN_GETMSG, &CLTCLOOkDlg::OnBnClickedBtnGetmsg)
	ON_COMMAND(ID_ABOUT, &CLTCLOOkDlg::OnAbout)
	ON_COMMAND(ID_DLG_REGBOX, &CLTCLOOkDlg::OnDlgRegbox)
	ON_MESSAGE(WM_ICON_NOTIFY,OnTrayNotify)
//	ON_WM_NOTIFYFORMAT()
ON_WM_SIZE()
ON_COMMAND(ID_M_ALERT, &CLTCLOOkDlg::OnMAlert)
END_MESSAGE_MAP()


// CLTCLOOkDlg 消息处理程序

BOOL CLTCLOOkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);// 设置小图标
	 //IsWindowXP();
	 
	
	//SetTimer(1111,1000,NULL);
	//SetTimer(1110,4000,NULL);
	//SetTimer(2000,8000,NULL);
	
	

	// TODO: 在此添加额外的初始化代码
	if (reg.IsRegister())
	{
		this->SetWindowText("okcoin网BTC(比特币)看盘助手1.3[已注册]                                                   作者FJK   QQ:171938416");
	}
	else
	{
		this->SetWindowText("okcoin网BTC(比特币)看盘助手1.3[免费版本]                                                   作者FJK   QQ:171938416");

	}

	SetupTrayIcon(m_hWnd);
	AfxBeginThread(Gettradesthread,this);
	AfxBeginThread(GetDepththread,this);
	AfxBeginThread(GetTickerthread,this);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLTCLOOkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLTCLOOkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLTCLOOkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLTCLOOkDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent==1110)
	{
		//GetDepth();

	}
	if (nIDEvent==2000)
	{
		isfree();
	}
	if (nIDEvent=1111)
	{
		GetTicker();
		
		//OnBnClickedButton1();
	//	isfree();
		
	}
	if (nIDEvent==1112)
	{
		ishighalert=FALSE;
		KillTimer(1112);
	}
	if (nIDEvent==1113)
	{
		islowalert=false;
		KillTimer(1113);
	}
	if (nIDEvent==3000)
	{
		KillTimer(3000);
		CloseToolTip();

	}
	

	CDialog::OnTimer(nIDEvent);
}

bool CLTCLOOkDlg::GetDataApi(CString strURL,CString *strReturn)
{
	CInternetSession session;
	CHttpFile *pFile = NULL; 


	//CString strURL = "http://www.8088.com/static/public/ssc/xml/newlyopenlist.xml";//网址
	CString strHtmlText = _T("");
	try
	{
		pFile = (CHttpFile*)session.OpenURL(strURL, 1, INTERNET_FLAG_TRANSFER_ASCII|INTERNET_FLAG_RELOAD|INTERNET_FLAG_DONT_CACHE);
	}
	catch(CInternetException * m_pException)
	{

		pFile = NULL;
		char szError[MAX_PATH + 2];
		//m_pException->GetErrorMessage(szError, MAX_PATH);
	//	AfxMessageBox(szError);
		m_pException->Delete();
		session.Close();
		return 0;
	}
	CString strLine;
	if(pFile != NULL)
	{
		while(pFile->ReadString(strLine) != NULL)
		{
			strHtmlText += strLine;

		}
	}
	*strReturn=strHtmlText;
	//+		strHtmlText	"<html><head><title>502 Bad Gateway</title></head><body bgcolor="white"><center><h1>502 Bad Gateway</h1></center><hr><center>nginx/1.4.1</center></body></html>"	ATL::CStringT<char,StrTraitMFC<char,ATL::ChTraitsCRT<char> > >

	if (strReturn->Find("502 Bad Gateway")!=-1)
	{
		//AfxMessageBox("网络故障,请检查网络或服务器被攻击");
		Sleep(1000);
		exit(-1);
	}

	pFile->Close();
	delete pFile;
	session.Close();

	return false;
}
void CLTCLOOkDlg::GetTicker()
{
	 StrUrl=_T("https://www.okcoin.com/api/ticker.do");
	CString strtemp;
	strtemp="";
	GetDataApi(StrUrl,&strtemp);
	//{"ticker":{"buy":"212.65","high":"264.5","last":"212.7","low":"135.0","sell":"212.69","vol":"4829874.368"}}
	//AfxMessageBox(strtemp);
	if(strtemp.Find("ticker")==-1)
	{
		return ;
	}
	strtemp.Replace('"','(');
	//临时字符串保存数据
	CString strbuy="(buy(:(";
	CString strhigh="(high(:(";
	CString strlast="(last(:(";
	CString strlow="(low(:(";
	CString strsell="(sell(:(";
	CString strvol="(vol(:(";
	int ifisrt=strtemp.Find(strbuy)+strbuy.GetLength();
	int iend= strtemp.Find("(",ifisrt+1);
	strbuy=strtemp.Mid(ifisrt,iend-ifisrt);
	double buy=atof(strbuy);

	ifisrt=strtemp.Find(strhigh)+strhigh.GetLength();
	iend=strtemp.Find("(",ifisrt+1);
	strhigh=strtemp.Mid(ifisrt,iend-ifisrt);
	m_ticker.strhigh=strhigh;
	ifisrt=strtemp.Find(strlast)+strlast.GetLength();
	iend=strtemp.Find("(",ifisrt+1);
	strlast=strtemp.Mid(ifisrt,iend-ifisrt);

	ifisrt=strtemp.Find(strlow)+strlow.GetLength();
	iend=strtemp.Find("(",ifisrt+1);
	strlow=strtemp.Mid(ifisrt,iend-ifisrt);

	ifisrt=strtemp.Find(strsell)+strsell.GetLength();
	iend=strtemp.Find("(",ifisrt+1);
	strsell=strtemp.Mid(ifisrt,iend-ifisrt);


	ifisrt=strtemp.Find(strvol)+strvol.GetLength();
	iend=strtemp.Find("(",ifisrt+1);
	strvol=strtemp.Mid(ifisrt,iend-ifisrt);

	//给结构体变量赋值
	m_ticker.strbuy=strbuy;
	m_ticker.strhigh=strhigh;
	m_ticker.strlast=strlast;
	m_ticker.strlow=strlow;
	m_ticker.strsell=strsell;
	m_ticker.strvol=strvol;

	//显示数据到窗体
	SetDlgItemText(IDC_EDIT_BUY,strbuy);
	SetDlgItemText(IDC_EDIT_HIGH,strhigh);
	SetDlgItemText(IDC_EDIT_LAST,strlast);
	SetDlgItemText(IDC_EDIT_LOW,strlow);
	SetDlgItemText(IDC_EDIT_SELL,strsell);
	SetDlgItemText(IDC_EDIT_VOL,strvol);

}
void CLTCLOOkDlg::GetDepth()
{
	CString strdepthurl="https://www.okcoin.com/api/depth.do";
	CString strtemp;
	strtemp="";
	GetDataApi(strdepthurl,&strtemp);
	//AfxMessageBox(strtemp);
	//if (strtemp.Find(Strsk)==-1)
	//{
//		return ;
//	}
	CString Strsks,StrBids;
	int ifirst=strtemp.Find("[[");
	int iend= strtemp.Find("]]")+2;
	Strsks=strtemp.Mid(ifirst,iend-ifirst+1);
	//AfxMessageBox(Strsks);
	CString istrtemp;
	CString istrtemp2;
	CClientDC dc(this);
	//SetBkMode(dc, TRANSPARENT);
	//SetBkMode(dc, OPAQUE);
	dc.SetTextColor(RGB(0,0,255));
// 	if (IsWindowXP())
// 	{
// 		//dc.SetBkColor(RGB(233,233,233));
// 		dc.SetBkColor(RGB(236,233,216));
// 	}else
// 	{
// 		dc.SetBkColor(RGB(240,240,240));
// 	}
	dc.SetBkColor(GetSysColor(COLOR_BTNFACE));
	for (int i=1;i<20;i++)
	{ 
		if(i<10)
		{
			istrtemp2.Format("卖(%d) :       " ,i);
		}
		else
		{
			istrtemp2.Format("卖(%d):      " ,i);

		}
		istrtemp=Strsks.Right(Strsks.GetLength()-Strsks.ReverseFind('[')-1);
		int length=istrtemp.GetLength();

		istrtemp=istrtemp.Left(istrtemp.Find(']'));

		istrtemp.Replace(",","       ");
		istrtemp2+=istrtemp;
		//AfxMessageBox(istrtemp2);
		Strsks=Strsks.Left(Strsks.GetLength()-length-2);
		TextOut(dc,340,96+(i+1)*24,"                                                  ",50);
		TextOut(dc,340,96+(i+1)*24,istrtemp2,strlen(istrtemp2));
		//	DrawText(dc,)
		//AfxMessageBox(Strsks);
	}
	StrBids=strtemp.Right(strtemp.GetLength()-iend);
	//AfxMessageBox(StrBids);
	StrBids=StrBids.Right(StrBids.GetLength()-StrBids.Find("[[")-1);
	//AfxMessageBox(StrBids);
	dc.SetTextColor(RGB(255,0,255));
	for (int i=1;i<20;i++)
	{ 
		if(i<10)
		{
			istrtemp2.Format("买(%d):      " ,i);

		}
		else
		{
			istrtemp2.Format("买(%d):    " ,i);

		}
		istrtemp=StrBids.Left(StrBids.Find(']'));
		istrtemp=istrtemp.Right(istrtemp.GetLength()-1);
		istrtemp.Replace(",","       ");
		istrtemp2+=istrtemp;
		StrBids=StrBids.Right(StrBids.GetLength()-StrBids.Find(",[")-1);
		TextOut(dc,28,96+(i+1)*24,"                                                  ",50);
		TextOut(dc,28,96+(i+1)*24,istrtemp2,strlen(istrtemp2));

	}

}


void CLTCLOOkDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strdepthurl="https://www.okcoin.com/api/trades.do";
	CString strtemp;
	strtemp=" ";
	

	//获取数据验证数据是否接收正确
	GetDataApi(strdepthurl,&strtemp);
	if (strtemp==" ")
	{
		//AfxMessageBox("网络链接存在问题 请查证");
		return ;
	}
	strtemp.Replace('"','*');
	//strtemp.Left(strtemp.GetLength()-1);
	if (strtemp.Find("[{*amount*:*")==-1)
	{
		//AfxMessageBox("获取数据错误 请检查网络");
		return ;
	}


	CString stramount;
	CString strdata;
	CString strprice;
	CString strtid;
	CString strtype;
	CString istrtemp;
	CString istrtemp2;
	CClientDC dc(this);
	int icount;

		dc.SetBkColor(GetSysColor(COLOR_BTNFACE));

	
	

	for(int i=1;i<15;i++)
	{
		stramount="{*amount*:*";
		strdata=",*date*:";
		strprice="*price*:*";
		strtid="*tid*:";
		strtype="*type*:*";

	
		istrtemp=strtemp.Right(strtemp.GetLength()-strtemp.ReverseFind('{'));
		//AfxMessageBox(istrtemp);
	int istrlengh=istrtemp.GetLength();
	//TRACE(istrtemp);
	
	int ifirst=istrtemp.Find(stramount)+stramount.GetLength();
	int iend=istrtemp.Find("*,",ifirst);
	stramount=istrtemp.Mid(ifirst,iend-ifirst);
	
	//AfxMessageBox(stramount);
	
	ifirst=istrtemp.Find(strdata)+strdata.GetLength();
	iend=istrtemp.Find(',',ifirst);
	strdata=istrtemp.Mid(ifirst,iend-ifirst);
	
	ifirst=istrtemp.Find(strprice)+strprice.GetLength();
	iend=istrtemp.Find("*,",ifirst);
	strprice=istrtemp.Mid(ifirst,iend-ifirst);
    icount=strprice.GetLength();
	ifirst=istrtemp.Find(strtid)+strtid.GetLength();
	iend=istrtemp.Find(',',ifirst);
	strtid=istrtemp.Mid(ifirst,iend-ifirst);

	ifirst=istrtemp.Find(strtype)+strtype.GetLength();
	iend=istrtemp.Find('*',ifirst);
	strtype=istrtemp.Mid(ifirst,iend-ifirst);
	if(i==1)
	{
		m_trades.stramount=stramount;
		m_trades.strdata=strdata;
		m_trades.strprice=strprice;
		m_trades.strtid=strtid;
		m_trades.strtype=strtype;
		
		//预警判断
		if(IsAlert)
		{
			PriceAlert();

		}


	}
	if (strtype=="buy")
	{
		dc.SetTextColor(RGB(255,0,255));
	}
	else
	{
		dc.SetTextColor(RGB(0,0,255));
	}
	CTime time;
	time=atoi(strdata);
	strdata=time.Format("%H:%M:%S");
	
	istrtemp2.Format("%s                 %s                                ",strdata,strprice);


	//字符串对齐
	if(icount==3)
	{
		istrtemp2.Insert(51+2,stramount);

	}
	else
	{
		istrtemp2.Insert(51+(6-icount),stramount);

	}
	
	TextOut(dc,620,240+i*24,"                                                                                       ",strlen("                                                                                       "));
	TextOut(dc,620,240+i*24,istrtemp2,istrtemp2.GetLength());
	TRACE("%d\r\n",istrtemp2.GetLength());
	strtemp=strtemp.Left(strtemp.GetLength()-istrlengh);
	}
	
	
	


}

void CLTCLOOkDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);
CString strtext;
GetDlgItemText(IDC_BUTTON2,strtext);
double fprice=atof(m_trades.strprice);
if (strtext=="预警")
{
	if (m_high==0&&m_low==0)
	{
		AfxMessageBox("请设置预警价格");
		return ;

	}
	if (m_high<=fprice&&m_high!=0)
	{
		AfxMessageBox("高于价格设置错误,请重新输入");
		return ;
	}
	if (m_low>=fprice&&m_low!=0)
	{
		AfxMessageBox("低于价格设置错误,请重新输入");
		return ;
	}
	SetDlgItemText(IDC_BUTTON2,"取消预警");
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	IsAlert=TRUE;
}
else
{
	SetDlgItemText(IDC_BUTTON2,"预警");
	GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
	if (ishighalert)
	{
		ishighalert=false;
		KillTimer(1112);
	}
	if (islowalert)
	{
		islowalert=false;
		KillTimer(1113);
	}
	
	IsAlert=FALSE;
}
}
	
	

void CLTCLOOkDlg::PriceAlert()   //预警判断函数
{
	m_fprice=atof(m_trades.strprice);
	
	
	if (m_high<=m_fprice&&!islowalert&&!ishighalert&&m_high!=0)
	{
		ishighalert=TRUE;

		m_strMsg.Format("价格高于预警值:%2f",m_high);
// 		OpenMedia("C:\\OutPath\\我赚钱了.wav");
// 		mciSendString("play MYAUDIOPLAYER",NULL,0,NULL);
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1),AfxGetResourceHandle(), SND_ASYNC|SND_RESOURCE|SND_NODEFAULT|SND_LOOP);

		if (AfxMessageBox(m_strMsg)==1)
		{
			//mciSendString("close MYAUDIOPLAYER",NULL,0,NULL);
			PlaySound(NULL,NULL,SND_FILENAME);
			SetTimer(1112,30*1000,NULL);
		}
		
	}
	if (m_low!=0)
	{
		if (m_low>=m_fprice&&!ishighalert&&!islowalert)
		{
			islowalert=TRUE;
			m_strMsg.Format("价格低于预警值%2f",m_low);
			PlaySound(MAKEINTRESOURCE(IDR_WAVE1),AfxGetResourceHandle(), SND_ASYNC|SND_RESOURCE|SND_NODEFAULT|SND_LOOP);
			if (AfxMessageBox(m_strMsg)==1)
			{
				PlaySound(NULL,NULL,SND_FILENAME);
				SetTimer(1113,30*3000,NULL);
			}
		}
	}
	

}

BOOL CLTCLOOkDlg::OpenMedia(CString lpszName)
{
	MCI_OPEN_PARMS mciopen ;
	CString strMusic =lpszName;
	CString strExtent=strMusic.Right(3);
	if (strExtent=="wav")
	{
		mciopen.lpstrDeviceType="waveaudio";

	}
	else
	{
		mciopen.lpstrDeviceType="mpegvideo";

	}
	mciopen.lpstrElementName=strMusic;
	mciopen.lpstrAlias="MYAUDIOPLAYER";

	int nError;
	nError=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT|MCI_OPEN_ALIAS|MCI_OPEN_TYPE,(DWORD)&mciopen);
	if (nError!=0)
	{
		char szerror[MAX_PATH];
		mciGetErrorString(nError,szerror,MAX_PATH);
		AfxMessageBox(szerror);
		return FALSE;
	}
	return TRUE ;

	
}
BOOL CLTCLOOkDlg::isfree()
{
	//CTime time;
	//time=atoi(m_trades.strdata)-1386814098;
	//CString strt=time.Format("%H:%M:%S");
	//AfxMessageBox(strt);
	//int i=time.GetDay();
	CTime time,time1;
	time=atoi(m_trades.strdata);
	time1=1386814098;
	int i=atoi(time.Format("%d"));
	int b=atoi(time1.Format("%d"));
	
//时间限制
// 	if (atoi(time.Format("%d"))-atoi(time1.Format("%d")) >= 7)
// 	{
// 		KillTimer(2000);
// // 		if(AfxMessageBox("免费时间已过,请联系Q:171938416 软件注册价格:10元")==1)
// // 		{
// // 
// // 		exit(-1);
// // 		}
// 		if (!reg.IsRegister())
// 		{
// 			CSotfRegDlg dlg;
// 			dlg.DoModal();
// 			exit(-1);	
// 		}
// 		
// 	}
// 	else
// 	{
// 		return TRUE ;
// 	}
return TRUE;
}


void CLTCLOOkDlg::OnBnClickedBtnGetmsg()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strSendMsg;
	
	if (OpenClipboard())
	{
		strSendMsg.Format("看盘助手提醒\r\nOKCoin BTC最新价格\r\n BTC最新成交价%s元\r\n BTC成交总量:%s\r\n 看盘助手提供(QQ 171938416)",m_trades.strprice,m_ticker.strvol);
		HANDLE hclip;
		char *pbuff;
		EmptyClipboard();
		hclip=GlobalAlloc(GMEM_MOVEABLE,strSendMsg.GetLength()+1);
		pbuff=(char*) GlobalLock(hclip);
		strcpy(pbuff,strSendMsg);
		GlobalUnlock(hclip);
		SetClipboardData(CF_TEXT,hclip);
		CloseClipboard();

	}

}

void CAboutDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	
}

void CLTCLOOkDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CLTCLOOkDlg::OnDlgRegbox()
{
	// TODO: 在此添加命令处理程序代码
	CSotfRegDlg softdlg;
	softdlg.DoModal();

	
	
}
BOOL  CLTCLOOkDlg::IsWindowXP()
{
	DWORD dwVersion = GetVersion();
	DWORD dwdwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
	DWORD dwWindowsMinorVersion =  (DWORD)(HIBYTE(LOWORD(dwVersion)));
	CString strversion;
// 	strversion.Format("%d",dwdwWindowsMajorVersion);
// 	AfxMessageBox(strversion);

	// Get the build number.

	if (dwdwWindowsMajorVersion < 6)              // Windows NT/2000/XP
	{
		m_b_WindowXP=TRUE;
		return TRUE ;
	}
	else
	{
		m_b_WindowXP=FALSE;
		return FALSE ;
	}

}

//UINT CLTCLOOkDlg::OnNotifyFormat(CWnd *pWnd, UINT nCommand)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	return CDialog::OnNotifyFormat(pWnd, nCommand);
//}
BOOL CLTCLOOkDlg::SetupTrayIcon(HWND hwnd)
{
	//ZeroMemory(&m_tnd, sizeof(NOTIFYICONDATA));
	m_tnd.cbSize              = sizeof( NOTIFYICONDATA );
	m_tnd.hWnd              = hwnd;//this->GetSafeHwnd();//所在对话框窗口句柄
	m_tnd.uID              = IDR_MAINFRAME;
	m_tnd.uFlags              = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	//m_tnd.dwInfoFlags      = NIIF_USER;

	m_tnd.uCallbackMessage = WM_ICON_NOTIFY;  
	//m_tnd.uTimeout         = 3;
	m_tnd.hIcon                 = m_hIcon;//需要指定一个图标！这里是所在对话框的图标
	strcpy_s(m_tnd.szTip,_T("我的任务栏程序"));
	return Shell_NotifyIcon( NIM_ADD, &m_tnd );
}

BOOL CLTCLOOkDlg::RemoveTrayIcon()
{
	return Shell_NotifyIcon( NIM_DELETE, &m_tnd );
}

BOOL CLTCLOOkDlg::cltShowToolTip(LPCTSTR szMsg,LPCTSTR szTitle,DWORD dwInfoFlags,UINT uTimeout)
{
	m_tnd.cbSize=sizeof(NOTIFYICONDATA);
	m_tnd.uFlags = NIF_TIP;
	m_tnd.uVersion = NOTIFYICON_VERSION;
	//m_tnd.uTimeout = uTimeout;
	m_tnd.dwInfoFlags = dwInfoFlags;
	//strcpy_s( m_tnd.szInfoTitle, szTitle );//气泡标题
	//strcpy_s( m_tnd.szInfo,      szMsg     );//气泡内容
	strcpy_s( m_tnd.szTip,  szMsg);
	SetTimer(3000, uTimeout, NULL);
	return Shell_NotifyIcon( NIM_MODIFY, &m_tnd );
}


BOOL CLTCLOOkDlg::CloseToolTip()
{
	m_tnd.cbSize=sizeof(NOTIFYICONDATA);
	m_tnd.uFlags = NIF_INFO;
	strcpy_s( m_tnd.szInfo,      _T("")     );//气泡内容 设置为空即可取消气泡提示
	return Shell_NotifyIcon( NIM_MODIFY, &m_tnd );
}



 

void CLTCLOOkDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	RemoveTrayIcon();

	CDialog::OnCancel();
}

void CLTCLOOkDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if (nType==SIZE_MINIMIZED)
	{
		SetupTrayIcon(m_hWnd);
	}

	// TODO: 在此处添加消息处理程序代码
}
//托盘消息映射函数
LRESULT CLTCLOOkDlg::OnTrayNotify(WPARAM wParam,LPARAM lParam)
{
	UINT uMouseMsg=(UINT)lParam;
	switch(uMouseMsg)
	{
	case WM_LBUTTONDBLCLK:
	case WM_RBUTTONDBLCLK:
			ShowWindow(SW_SHOWNORMAL);
			RemoveTrayIcon();

	
		break;
	case WM_MOUSEMOVE:
		CString strtip;
		strtip.Format("看盘助手提醒\r\nOKCoin BTC最新价格\r\n BTC最新成交价%s元\r\n BTC成交总量:%s\r\n 看盘助手提供(QQ 171938416)",m_trades.strprice,m_ticker.strvol);
		cltShowToolTip(strtip,strtip,m_tnd.dwInfoFlags,3000);
		break;

	}
	return 0;
}
UINT Gettradesthread(LPVOID lpParam)
{
	CLTCLOOkDlg *dlg=(CLTCLOOkDlg *)lpParam;
	while (TRUE)
	{
		if (IsfreeDC)
		{
			IsfreeDC=FALSE;
			dlg->OnBnClickedButton1();
			IsfreeDC=TRUE;
		}
		Sleep(500);
	}
	//dlg->OnBnClickedButton1();

	return 0;
}
UINT GetDepththread(LPVOID lpParam)
{
	CLTCLOOkDlg *dlg=(CLTCLOOkDlg *)lpParam;
	while (TRUE)
	{
		if (IsfreeDC)
		{
			IsfreeDC=FALSE;
		dlg->GetDepth();
		IsfreeDC=TRUE;
		}
		Sleep(500);
	}
	//dlg->OnBnClickedButton1();

	return 0;
}

UINT GetTickerthread(LPVOID lpParam)
{
	CLTCLOOkDlg *dlg=(CLTCLOOkDlg *)lpParam;
	while (TRUE)
	{
		if (IsfreeDC)
		{
			IsfreeDC=FALSE;
			dlg->GetTicker();
			IsfreeDC=TRUE;
		}
		Sleep(500);
	}
	//dlg->OnBnClickedButton1();

	return 0;
}

//报警设置
void CLTCLOOkDlg::OnMAlert()
{
	// TODO: 在此添加命令处理程序代码

}
