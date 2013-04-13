#pragma once
#include "CDate_base.h"

class CDate_Class :
	public CDate_base
{
public:
	CDate_Class(void);
	virtual ~CDate_Class(void);

public:
	CString m_name;
	CString m_num;
	CString m_pName;
	CString m_tellPhone;
	CString m_contact;
	CString m_detail;
};
