#pragma once
#include "cdata_bace.h"

class CData_admin :
	public CData_bace
{
public:
	CData_admin(void);
	virtual ~CData_admin(void);

public:
	CString m_user;
	CString m_password;
};
