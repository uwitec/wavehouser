#pragma once
#include "CControl_bace.h"
#include "CDate_User.h"
#include "CStringTransform.h"
#include <string>

using namespace std;
class CControl_Login
{
public:
	CControl_Login(void);
	~CControl_Login(void);

	void SetData(const CDate_User *data);
	void SetData( const CString &user,const CString &pass );
	bool Search();
	bool Search(const CString &user,const CString &pass );
private:
	CDate_User m_loginUser;
	CStringTransform m_dataChange;
};
