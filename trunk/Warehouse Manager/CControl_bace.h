#pragma once
//#include "CControl_DB.h"
#include "CDate_base.h"
#include "CDate_admin.h"
#include "CDate_Warehouse.h"
#include "CDate_Company.h"
#include "CDate_User.h"
#include "CStringTransform.h"
class CControl_bace
{
public:
	CControl_bace(void);
	~CControl_bace(void);

	virtual void SetData(const CDate_base *data);

	virtual bool Save();
	virtual bool Delete();
	virtual bool Updata();
	virtual bool Search();

	CStringTransform m_dateChange;

	static CDate_admin s_user;
	static CDate_warehouse s_wareHouse;
	static CDate_Company s_company;
	static CDate_User s_userInfo;
private:
	CDate_base *m_data;
};
