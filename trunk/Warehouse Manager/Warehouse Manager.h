// Warehouse Manager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWarehouseManagerApp:
// �йش����ʵ�֣������ Warehouse Manager.cpp
//

class CWarehouseManagerApp : public CWinApp
{
public:
	CWarehouseManagerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CWarehouseManagerApp theApp;