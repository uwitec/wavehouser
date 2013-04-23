#pragma once
#include "CControl_bace.h"
#include "CDate_Class.h"
class CControl_class :public CControl_bace
{
public:
	CControl_class(void);
	virtual ~CControl_class(void);

	void SetData(CDate_Class *data);

	bool Save();
	bool Delete();
	bool Updata();
	bool Search();
	CDate_Class Search_byId(const string &id);
	vector<CDate_Class> SearchList_Class(const CDate_search &condition);
private:
	CDate_Class *m_data;
};
