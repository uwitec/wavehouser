#pragma once
#include "CControl_bace.h"
#include "CDate_Company.h"
class CControl_company :public CControl_bace
{
public:
	CControl_company(void);
	virtual ~CControl_company(void);

	void SetData(const CDate_Company *data);

	bool Save();
	bool Delete();
	bool Updata();
	bool Search();
private:
	CDate_Company *m_data;
};
