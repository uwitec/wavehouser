#pragma once
#include "CControl_bace.h"
#include "CDate_User.h"
#include "CStringTransform.h"
class CControl_Login
{
public:
	CControl_Login(void);
	~CControl_Login(void);

	void SetData(const CDate_User *data);

	bool Search();
private:
	CDate_User m_loginUser;
	CStringTransform m_dataChange;
};
