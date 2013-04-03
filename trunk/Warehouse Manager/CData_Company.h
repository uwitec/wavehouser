#pragma once
#include "CData_bace.h"
class CData_Company:public CData_bace
{
public:
	CData_Company(void);
	~CData_Company(void);

public:
	CString m_companyName;
	CString m_wareName;
	CString m_wareId;
	CString m_address;
	CString m_tellPhone;
	CString m_tellMan;
	CString m_detail;
};
