
// autoCreateLable.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CautoCreateLableApp: 
// �йش����ʵ�֣������ autoCreateLable.cpp
//

class CautoCreateLableApp : public CWinApp
{
public:
	CautoCreateLableApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CautoCreateLableApp theApp;