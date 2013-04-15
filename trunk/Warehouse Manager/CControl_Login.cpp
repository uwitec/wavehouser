#include "StdAfx.h"
#include "CControl_Login.h"
#include "ADOOperate.h"

CControl_Login::CControl_Login(void)
{
}

CControl_Login::~CControl_Login(void)
{
}

void CControl_Login::SetData( const CDate_User *data )
{
	m_loginUser = *data;
}

bool CControl_Login::Search()
{
	CADOOperate::InitADO();
	string sql = "select * from tab_admin where admin_name='";
	sql += m_dataChange.CStringtostring(m_loginUser.m_name);
	sql += "' and admin_password='";
	sql +=  m_dataChange.CStringtostring(m_loginUser.m_pass);

	_RecordsetPtr tmp;

	return CADOOperate::GetRecordsCount(tmp,sql) == 1;
}
