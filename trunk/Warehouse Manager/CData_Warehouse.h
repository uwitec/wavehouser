#pragma once
#include "cdata_bace.h"

class CData_warehouse :
	public CData_bace
{
public:
	CData_warehouse(void);
	virtual ~CData_warehouse(void);

public:
	CString m_name;

};
