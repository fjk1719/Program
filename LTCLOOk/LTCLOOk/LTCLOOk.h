// LTCLOOk.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLTCLOOkApp:
// �йش����ʵ�֣������ LTCLOOk.cpp
//

class CLTCLOOkApp : public CWinApp
{
public:
	CLTCLOOkApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLTCLOOkApp theApp;