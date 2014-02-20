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

	void BuildHardWareID();   //机器码生成器
	CString GetHardWareID();//获取当前机器机器码
	void SetHardWareID(CString core); //设置机器码


	void BuildHardWareKey(); //生成注册码
	
	CString GetHardwareKey();//获取注册码
	BOOL WriteHardWareKey(CString StrKey);//写注册码到注册表
	BOOL ReadRegHardwareKey(CString * StrKey); //取注册表中注册码
	BOOL IsRegister();//判断是否注册


	void SetName(CString name);
	CString GetName();

	void SetCooe(CString cooe);
	CString GetCooe();

	CString Chgetoox(CString str);
	

};
