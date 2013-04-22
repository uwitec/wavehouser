#pragma once
#include "CControl_bace.h"
#include "CDate_check.h"
class CControl_check :public CControl_bace
{
public:
	CControl_check(void);
	virtual ~CControl_check(void);

	void SetData(CDate_check *data);

	bool Save();
	bool Delete();
	bool Updata();
	bool Search();
	vector<CDate_check> SearchList_Check(CDate_search condition);
private:
	CDate_check *m_data;
};
