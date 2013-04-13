#pragma once
#include "CControl_bace.h"
#include "CDate_user.h"
class CControl_user :public CControl_bace
{
public:
	CControl_user(void);
	virtual ~CControl_user(void);

	void SetData(const CDate_User *data);

	bool Save();
	bool Delete();
	bool Updata();
	bool Search();
private:
	CDate_User *m_data;
};
