#pragma once
#include "CDate_base.h"

class CDate_admin :
	public CDate_base
{
public:
	CDate_admin(void);
	virtual ~CDate_admin(void);

public:
	CString m_user;
	CString m_password;

private:
	CDate_base m_base;
};
