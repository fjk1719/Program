#pragma once

class CCooe
{
public:
	CCooe(void);
	~CCooe(void);

protected:

	CString m_CpuCore;
	CString m_ZuQueMa;
	CString m_name;
	CString m_cooe;
	CString m_RegPath;
public:

	void BuildHardWareID();   //������������
	CString GetHardWareID();//��ȡ��ǰ����������
	void SetHardWareID(CString core); //���û�����


	void BuildHardWareKey(); //����ע����
	
	CString GetHardwareKey();//��ȡע����
	BOOL WriteHardWareKey(CString StrKey);//дע���뵽ע���
	BOOL ReadRegHardwareKey(CString * StrKey); //ȡע�����ע����
	BOOL IsRegister();//�ж��Ƿ�ע��


	void SetName(CString name);
	CString GetName();

	void SetCooe(CString cooe);
	CString GetCooe();

	CString Chgetoox(CString str);
	

};
