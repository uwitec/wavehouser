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

};
