#pragma once
#include "CDate_base.h"

class CDate_Material :
	public CDate_base
{
public:
	CDate_Material(void);
	virtual ~CDate_Material(void);

public:
	CString m_name;
	CString m_modal;
	CString m_manufacturer;
	CString m_unit;
	CString m_price;
	CString m_detail;
	CString m_total;
};
