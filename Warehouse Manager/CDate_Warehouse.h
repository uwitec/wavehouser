#pragma once
#include "CDate_base.h"

class CDate_warehouse :
	public CDate_base
{
public:
	CDate_warehouse(void);
	virtual ~CDate_warehouse(void);

public:
	CString m_name;
	CString m_cname;
	CString m_aname;
	CString m_tell;
	CString m_email;
	CString m_detail;

private:
	CDate_base m_base;
};
