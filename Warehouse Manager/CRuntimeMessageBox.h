#pragma once

#include "CStringTransform.h"
class CRuntimeMessageBox
{
public:
	CRuntimeMessageBox(void){};
	~CRuntimeMessageBox(void){};

	static int RunMessageBox(const string &msg)
	{
		CStringTransform tmp;
		return ::MessageBox(::GetActiveWindow(),tmp.stringToCstring(msg),_T("��ʾ"),MB_OK);
	};
};

