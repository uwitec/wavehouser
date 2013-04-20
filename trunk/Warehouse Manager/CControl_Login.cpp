#include "StdAfx.h"
#include "CControl_Login.h"
//#include "CControl_DB.h"

//extern CControl_DB_sqlite g_sqlite;

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
void CControl_Login::SetData( const CString &user,const CString &pass )
{
	m_loginUser.m_name = user;
	m_loginUser.m_pass = pass;
}

bool CControl_Login::Search(const CString &user,const CString &pass )
{
	string sql = "select * from tab_admin where admin_name='";
	sql += m_dataChange.CStringtostring(user);
	sql += "' and admin_pass='";
	sql +=  m_dataChange.CStringtostring(pass);
	sql += "'";

	SQLiteStatement* stmt=g_sqlite.Statement(sql);

	while(stmt->NextRow())
	{
		CControl_bace::s_user.SetId(stmt->ValueString (0));
		CControl_bace::s_user.m_user = m_dataChange.stringToCstring(stmt->ValueString (1));
		CControl_bace::s_user.m_password = m_dataChange.stringToCstring(stmt->ValueString (2));

		break;
	}

// 	string sql = "select * from tab_admin where admin_name='";
// 	sql += m_dataChange.CStringtostring(user);
// 	sql += "' and admin_pass='";
// 	sql +=  m_dataChange.CStringtostring(pass);
// 	sql += "'";
// 
// 	_RecordsetPtr tmp;
// 
// 	CADOOperate::OpenRecordset(tmp,sql);
// 	while(!tmp->adoEOF)
// 	{
// 		CControl_bace::s_user.SetId(CADOOperate::GetCollectData(tmp,"id"));
// 		CControl_bace::s_user.m_user = m_dataChange.stringToCstring(CADOOperate::GetCollectData(tmp,"admin_name"));
// 		CControl_bace::s_user.m_password = m_dataChange.stringToCstring(CADOOperate::GetCollectData(tmp,"admin_pass"));
// 
// 		break;
// 	}
// 
 	return !CControl_bace::s_user.GetId().empty();
}
bool CControl_Login::Search()
{
	//CADOOperate::InitADO();
	//string sql = "select * from tab_admin where admin_name='";
	//sql += m_dataChange.CStringtostring(m_loginUser.m_name);
	//sql += "' and admin_pass='";
	//sql +=  m_dataChange.CStringtostring(m_loginUser.m_pass);

	//_RecordsetPtr tmp;

	//return CADOOperate::GetRecordsCount(tmp,sql) == 1;

	return false;
}
