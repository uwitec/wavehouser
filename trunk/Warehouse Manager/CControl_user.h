#pragma once
#include "CControl_bace.h"
#include "CDate_user.h"
class CControl_user :public CControl_bace
{
public:
	CControl_user(void);
	virtual ~CControl_user(void);

	void SetData(CDate_User *data);

	bool Save(const bool &isSelf = true);
	bool Delete();
	bool Updata();
	bool Search(const bool &isSelf = true);
	vector<CDate_User> SearchList_UserInfo(CDate_search condition);
private:
	CDate_User *m_data;
};
