// LTCLOOkDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
CCooe reg;

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLTCLOOkDlg �Ի���




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


// CLTCLOOkDlg ��Ϣ�������

BOOL CLTCLOOkDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);// ����Сͼ��
	 //IsWindowXP();
	 
	
	//SetTimer(1111,1000,NULL);
	//SetTimer(1110,4000,NULL);
	//SetTimer(2000,8000,NULL);
	
	

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	if (reg.IsRegister())
	{
		this->SetWindowText("okcoin��BTC(���ر�)��������1.3[��ע��]                                                   ����FJK   QQ:171938416");
	}
	else
	{
		this->SetWindowText("okcoin��BTC(���ر�)��������1.3[��Ѱ汾]                                                   ����FJK   QQ:171938416");

	}

	SetupTrayIcon(m_hWnd);
	AfxBeginThread(Gettradesthread,this);
	AfxBeginThread(GetDepththread,this);
	AfxBeginThread(GetTickerthread,this);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLTCLOOkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLTCLOOkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CLTCLOOkDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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


	//CString strURL = "http://www.8088.com/static/public/ssc/xml/newlyopenlist.xml";//��ַ
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
		//AfxMessageBox("�������,��������������������");
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
	//��ʱ�ַ�����������
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

	//���ṹ�������ֵ
	m_ticker.strbuy=strbuy;
	m_ticker.strhigh=strhigh;
	m_ticker.strlast=strlast;
	m_ticker.strlow=strlow;
	m_ticker.strsell=strsell;
	m_ticker.strvol=strvol;

	//��ʾ���ݵ�����
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
			istrtemp2.Format("��(%d) :       " ,i);
		}
		else
		{
			istrtemp2.Format("��(%d):      " ,i);

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
			istrtemp2.Format("��(%d):      " ,i);

		}
		else
		{
			istrtemp2.Format("��(%d):    " ,i);

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strdepthurl="https://www.okcoin.com/api/trades.do";
	CString strtemp;
	strtemp=" ";
	

	//��ȡ������֤�����Ƿ������ȷ
	GetDataApi(strdepthurl,&strtemp);
	if (strtemp==" ")
	{
		//AfxMessageBox("�������Ӵ������� ���֤");
		return ;
	}
	strtemp.Replace('"','*');
	//strtemp.Left(strtemp.GetLength()-1);
	if (strtemp.Find("[{*amount*:*")==-1)
	{
		//AfxMessageBox("��ȡ���ݴ��� ��������");
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
		
		//Ԥ���ж�
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


	//�ַ�������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);
CString strtext;
GetDlgItemText(IDC_BUTTON2,strtext);
double fprice=atof(m_trades.strprice);
if (strtext=="Ԥ��")
{
	if (m_high==0&&m_low==0)
	{
		AfxMessageBox("������Ԥ���۸�");
		return ;

	}
	if (m_high<=fprice&&m_high!=0)
	{
		AfxMessageBox("���ڼ۸����ô���,����������");
		return ;
	}
	if (m_low>=fprice&&m_low!=0)
	{
		AfxMessageBox("���ڼ۸����ô���,����������");
		return ;
	}
	SetDlgItemText(IDC_BUTTON2,"ȡ��Ԥ��");
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	IsAlert=TRUE;
}
else
{
	SetDlgItemText(IDC_BUTTON2,"Ԥ��");
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
	
	

void CLTCLOOkDlg::PriceAlert()   //Ԥ���жϺ���
{
	m_fprice=atof(m_trades.strprice);
	
	
	if (m_high<=m_fprice&&!islowalert&&!ishighalert&&m_high!=0)
	{
		ishighalert=TRUE;

		m_strMsg.Format("�۸����Ԥ��ֵ:%2f",m_high);
// 		OpenMedia("C:\\OutPath\\��׬Ǯ��.wav");
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
			m_strMsg.Format("�۸����Ԥ��ֵ%2f",m_low);
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
	
//ʱ������
// 	if (atoi(time.Format("%d"))-atoi(time1.Format("%d")) >= 7)
// 	{
// 		KillTimer(2000);
// // 		if(AfxMessageBox("���ʱ���ѹ�,����ϵQ:171938416 ���ע��۸�:10Ԫ")==1)
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strSendMsg;
	
	if (OpenClipboard())
	{
		strSendMsg.Format("������������\r\nOKCoin BTC���¼۸�\r\n BTC���³ɽ���%sԪ\r\n BTC�ɽ�����:%s\r\n ���������ṩ(QQ 171938416)",m_trades.strprice,m_ticker.strvol);
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
	// TODO: �ڴ���������������
	
}

void CLTCLOOkDlg::OnAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CLTCLOOkDlg::OnDlgRegbox()
{
	// TODO: �ڴ���������������
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
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	return CDialog::OnNotifyFormat(pWnd, nCommand);
//}
BOOL CLTCLOOkDlg::SetupTrayIcon(HWND hwnd)
{
	//ZeroMemory(&m_tnd, sizeof(NOTIFYICONDATA));
	m_tnd.cbSize              = sizeof( NOTIFYICONDATA );
	m_tnd.hWnd              = hwnd;//this->GetSafeHwnd();//���ڶԻ��򴰿ھ��
	m_tnd.uID              = IDR_MAINFRAME;
	m_tnd.uFlags              = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	//m_tnd.dwInfoFlags      = NIIF_USER;

	m_tnd.uCallbackMessage = WM_ICON_NOTIFY;  
	//m_tnd.uTimeout         = 3;
	m_tnd.hIcon                 = m_hIcon;//��Ҫָ��һ��ͼ�꣡���������ڶԻ����ͼ��
	strcpy_s(m_tnd.szTip,_T("�ҵ�����������"));
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
	//strcpy_s( m_tnd.szInfoTitle, szTitle );//���ݱ���
	//strcpy_s( m_tnd.szInfo,      szMsg     );//��������
	strcpy_s( m_tnd.szTip,  szMsg);
	SetTimer(3000, uTimeout, NULL);
	return Shell_NotifyIcon( NIM_MODIFY, &m_tnd );
}


BOOL CLTCLOOkDlg::CloseToolTip()
{
	m_tnd.cbSize=sizeof(NOTIFYICONDATA);
	m_tnd.uFlags = NIF_INFO;
	strcpy_s( m_tnd.szInfo,      _T("")     );//�������� ����Ϊ�ռ���ȡ��������ʾ
	return Shell_NotifyIcon( NIM_MODIFY, &m_tnd );
}



 

void CLTCLOOkDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

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

	// TODO: �ڴ˴������Ϣ����������
}
//������Ϣӳ�亯��
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
		strtip.Format("������������\r\nOKCoin BTC���¼۸�\r\n BTC���³ɽ���%sԪ\r\n BTC�ɽ�����:%s\r\n ���������ṩ(QQ 171938416)",m_trades.strprice,m_ticker.strvol);
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

//��������
void CLTCLOOkDlg::OnMAlert()
{
	// TODO: �ڴ���������������

}
