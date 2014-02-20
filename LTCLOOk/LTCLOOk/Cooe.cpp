#include "StdAfx.h"
#include "Cooe.h"
#include <atlbase.h>

CCooe::CCooe(void)
{

	m_CpuCore="";
	m_ZuQueMa="";
	m_name="";
	m_cooe="";
	m_RegPath="SoftWare\\hardwaresoftware\\key";


}

CCooe::~CCooe(void)
{

}
void CCooe::BuildHardWareID()
{
	CString jnam="",jcooe="";
	jnam=Chgetoox(m_name);
	jcooe=Chgetoox(m_cooe);


	unsigned long s1,s2;     
    char sel;   
    sel='1';   
    CString MyCpuID,CPUID1,CPUID2;   
	__asm{   
	mov eax,01h   
	xor edx,edx   
	cpuid   
	mov s1,edx   
	mov s2,eax   
	}   
	CPUID1.Format("%08X%08X",s1,s2);   
	__asm{   
	mov eax,03h   
	xor ecx,ecx   
	xor edx,edx   
	cpuid   
	mov s1,edx   
	mov s2,ecx   
	}   
	CPUID2.Format("%08X%08X",s1,s2);   
    MyCpuID=jnam+CPUID1+CPUID2+jcooe;
	DWORD ser;
	char namebuf[128];
	char filebuf[128];
	::GetVolumeInformation("c:\\",namebuf,128,&ser,0,0,filebuf,128);



	CString strdisk=jnam;
	CString srdik="";
	srdik.Format("%0x",ser);
	strdisk+=srdik;
	strdisk+=jcooe;
	CString strmachine="";


	int jgint=strlen(MyCpuID);

	int i=2,it=0;
	for(i;i<10;i++)
	{
		it=jgint/i;
		strmachine+=MyCpuID.Mid(it,1);
	}
	//
	jgint=strlen(strdisk);
	i=2,it=0;
	for(i;i<10;i++)
	{
		it=jgint/i;
		strmachine+=strdisk.Mid(it,1);
	}


 	m_CpuCore=strmachine; 

}
CString CCooe::GetHardWareID(void)
{
	BuildHardWareID();
	return m_CpuCore;
}
void CCooe::BuildHardWareKey()
{
	CString code[16]={"td","eh","im","np","ru","vy","zc","gk",
	"pa","qb","fj","oq","wt","ei","nr","xu"};

	CString cadff;
	CString reg,stred;
	int num;

			stred=m_CpuCore;


	stred.MakeLower();
	int lien=strlen(stred);
	for(int i=0;i<lien;i++)
	{
		char p=stred.GetAt(i);
		if(p>='a'&&p<='f')
		{
			num=p-'a'+10;
		}
		else
		{
			num=p-'0';
		}
		CString tmp=code[num];
		reg+=tmp;
	}
	reg.MakeUpper();


	m_ZuQueMa=reg;
}
CString CCooe::GetHardwareKey(void)
{
	BuildHardWareKey();
	return m_ZuQueMa;
}
void CCooe::SetName(CString name)
{
	m_name=name;
}
CString CCooe::GetName(void)
{
	return m_name;
}
void CCooe::SetCooe(CString cooe)
{
	m_cooe=cooe;
}
CString CCooe::GetCooe(void)
{
	return m_cooe;
}
CString CCooe::Chgetoox(CString str)
{


CString ouall="";
CString outt="";

		 unsigned char  a1,a2;
		int i=0;
		while(str.GetAt(i)!='\0')
		{
			if(str.GetAt(i)<127 && str.GetAt(i) >0)//¿¼ÂÇÖÐÓ¢»ìºÏ
			{
				a1=str.GetAt(i);

				outt.Format("%d",a1);
				ouall+=outt;

				i++;
			}
			else
			{
				a1=str.GetAt(i);
				a2=str.GetAt(i+1);

				outt.Format("%0x",a1);
				ouall+=outt;
				outt.Format("%0x",a2);
				ouall+=outt;

				i+=2;
			}   
		}


	return ouall;
}
void CCooe::SetHardWareID(CString core)
{
	m_CpuCore=core;
}

BOOL CCooe::WriteHardWareKey(CString StrKey)
{
	CRegKey rk;
	HKEY hkey=NULL;
	if(rk.Open(HKEY_CURRENT_USER,m_RegPath)== ERROR_SUCCESS)
	{
		//rk.SetKeyValue("key",StrKey);
		rk.SetStringValue("key",StrKey);
		rk.Close();
		return TRUE;

	}
	else
	{
		if(rk.Create(HKEY_CURRENT_USER,m_RegPath)== ERROR_SUCCESS)
		{
			
			rk.SetStringValue("key",StrKey);
			rk.Close();
			return TRUE;
		}
	
		
		return FALSE;
		

	}


	return TRUE;
}
BOOL CCooe::ReadRegHardwareKey(CString  * StrKey)//¶ÁÈ¡Ê§°Ü·µ»Øerror´íÎó 
{
	
	CRegKey rk;
	//HKEY m_hKey;
	DWORD pCount=1024;
	CString KeyValue;
	char szValue[1024];
	LPCTSTR lKeyName="Key";
	if(rk.Open(HKEY_CURRENT_USER,m_RegPath)== ERROR_SUCCESS)
	{
		if(rk.QueryValue(szValue,lKeyName,& pCount)== ERROR_SUCCESS)
		{
			*StrKey=szValue;
			rk.Close();
			return TRUE;	
		}
		else
		{
			*StrKey="error";
			rk.Close();
			return FALSE;	
		}
	}
	rk.Close();
	return TRUE ;


}
BOOL CCooe::IsRegister()
{
	CString strkey;
		ReadRegHardwareKey(&strkey);
		GetHardWareID();
		if (strkey==GetHardwareKey())
		{
			//AfxMessageBox("×¢²á³É¹¦");
			return TRUE;
		}
		else
		{
			//AfxMessageBox("×¢²áÊ§°Ü");
		    return FALSE;
		}

}