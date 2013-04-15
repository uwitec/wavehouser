#pragma once
#include "CDate_base.h"

class CDate_User :
	public CDate_base
{
public:
	CDate_User(void);
	virtual ~CDate_User(void);

public:
	CString m_name;
	CString m_companyName;
	CString m_age;
	CString m_tellPhone;
	CString m_email;
	CString m_detail;
	CString m_pass;
};
