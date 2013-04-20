#pragma once
#include "CDate_base.h"
class CDate_Company:public CDate_base
{
public:
	CDate_Company(void);
	~CDate_Company(void);

public:
	CString m_companyName;
	CString m_wareName;
	CString m_wareId;
	CString m_address;
	CString m_tellPhone;
	CString m_tellMan;
	CString m_detail;
private:
	CDate_base m_base;
};
