#pragma once
#include "cdata_bace.h"

class CData_Material :
	public CData_bace
{
public:
	CData_Material(void);
	virtual ~CData_Material(void);

public:
	CString m_name;
	CString m_modal;
	CString m_manufacturer;
	CString m_udit;
	CString m_price;
	CString m_detail;
};
