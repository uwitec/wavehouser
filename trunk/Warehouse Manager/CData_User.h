#pragma once
#include "cdata_bace.h"

class CData_User :
	public CData_bace
{
public:
	CData_User(void);
	virtual ~CData_User(void);

public:
	CString m_name;
	CString m_companyName;
	CString m_age;
	CString m_tellPhone;
	CString m_email;
	CString m_detail;
};
