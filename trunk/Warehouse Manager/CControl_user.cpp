#include "StdAfx.h"
#include "CControl_user.h"

CControl_user::CControl_user(void)
{
}

CControl_user::~CControl_user(void)
{
}

void CControl_user::SetData( CDate_User *data )
{
	m_data = data;
}

bool CControl_user::Save(const bool &isSelf/* = true*/)
{
	if(isSelf)
	{
		if(CControl_bace::s_userInfo.GetId().empty())
		{
			m_data->CreateId();

			string sql = "insert into tab_user values('";
			sql += m_data->GetId();
			sql += "','";
			sql += CControl_bace::s_user.GetId();
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_name);
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_companyName);
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_age);
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_tellPhone);
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_email);
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_detail);
			sql += "','";
			sql += CControl_bace::s_user.GetId();
			sql += "','";
			sql += m_dateChange.GetCurTimes();
			sql +="','0')";

			return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
		}

		m_data->SetId(CControl_bace::s_userInfo.GetId());

		return Updata();
	}
	else
	{
		if(m_data->GetId().empty())
		{
			m_data->CreateId();

			string sql = "insert into tab_user values('";
			sql += m_data->GetId();
			sql += "','";
			sql += CControl_bace::s_userInfo.GetId();
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_name);
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_companyName);
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_age);
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_tellPhone);
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_email);
			sql += "','";
			sql += m_dateChange.CStringtostring(m_data->m_detail);
			sql += "','";
			sql += CControl_bace::s_user.GetId();
			sql += "','";
			sql += m_dateChange.GetCurTimes();
			sql +="','0')";

			return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
		}

		return Updata();
	}
}

bool CControl_user::Delete()
{
	if(m_data->GetId().empty())
		return false;
	string sql = "update tab_user set del_flag='1' where id='";
	sql += m_data->GetId();
	sql += "';";
	//return CADOOperate::ExecuteSQL(sql);
	return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
}

bool CControl_user::Updata()
{
	string sql = "update tab_user set user_name='";
	sql += m_dateChange.CStringtostring(m_data->m_name);
	sql += "', user_company='";
	sql += m_dateChange.CStringtostring(m_data->m_companyName);
	sql += "', user_age='";
	sql += m_dateChange.CStringtostring(m_data->m_age);
	sql += "', user_tellphone='";
	sql += m_dateChange.CStringtostring(m_data->m_tellPhone);
	sql += "', user_email='";
	sql += m_dateChange.CStringtostring(m_data->m_email);
	sql += "',detail='";
	sql += m_dateChange.CStringtostring(m_data->m_detail);
	sql += "',create_time='";
	sql += m_dateChange.GetCurTimes();
	sql +="' where id='";
	sql += m_data->GetId();
	sql += "';";
	//return CADOOperate::ExecuteSQL(sql);
	return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
}

bool CControl_user::Search(const bool &isSelf/* = true*/)
{
	if(isSelf)
	{
		string sql = "select * from tab_user where create_by='";
		sql += CControl_bace::s_user.GetId();
		sql += "'";

		SQLiteStatement* stmt=g_sqlite.Statement(sql);

		while(stmt->NextRow())
		{
			CControl_bace::s_userInfo.SetId(stmt->ValueString (0));
			CControl_bace::s_userInfo.m_name        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (2)));
			CControl_bace::s_userInfo.m_companyName = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (3)));
			CControl_bace::s_userInfo.m_age         = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (4)));
			CControl_bace::s_userInfo.m_tellPhone   = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (5)));
			CControl_bace::s_userInfo.m_email       = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (6)));
			CControl_bace::s_userInfo.m_detail      = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (7)));

			break;
		}
		// 
		// 	_RecordsetPtr tmp;
		// 	CADOOperate::OpenRecordset(tmp,sql);
		// 	while(!tmp->adoEOF)
		// 	{
		// 		CControl_bace::s_wareHouse.SetId(CADOOperate::GetCollectData(tmp,"id"));
		// 		CControl_bace::s_wareHouse.m_cname = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"company_name"));
		// 		CControl_bace::s_wareHouse.m_aname = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"admin_name"));
		// 		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"warehouse_name"));
		// 		CControl_bace::s_wareHouse.m_tell = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"admin_tellphone"));
		// 		CControl_bace::s_wareHouse.m_email = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"admin_email"));
		// 		CControl_bace::s_wareHouse.m_detail = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"detail"));
		// 
		// 		break;
		// 	}

		return !CControl_bace::s_userInfo.GetId().empty();
	}
	else
	{
		string sql = "select * from tab_user where am_id='";
		sql += CControl_bace::s_userInfo.GetId();
		sql +=", and create_by='";
		sql += CControl_bace::s_user.GetId();
		sql += "'";

		SQLiteStatement* stmt=g_sqlite.Statement(sql);

		while(stmt->NextRow())
		{
			CControl_bace::s_userInfo.SetId(stmt->ValueString (0));
			CControl_bace::s_userInfo.m_name        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (2)));
			CControl_bace::s_userInfo.m_companyName = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (3)));
			CControl_bace::s_userInfo.m_age         = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (4)));
			CControl_bace::s_userInfo.m_tellPhone   = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (5)));
			CControl_bace::s_userInfo.m_email       = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (6)));
			CControl_bace::s_userInfo.m_detail      = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (7)));

			break;
		}
		// 
		// 	_RecordsetPtr tmp;
		// 	CADOOperate::OpenRecordset(tmp,sql);
		// 	while(!tmp->adoEOF)
		// 	{
		// 		CControl_bace::s_wareHouse.SetId(CADOOperate::GetCollectData(tmp,"id"));
		// 		CControl_bace::s_wareHouse.m_cname = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"company_name"));
		// 		CControl_bace::s_wareHouse.m_aname = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"admin_name"));
		// 		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"warehouse_name"));
		// 		CControl_bace::s_wareHouse.m_tell = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"admin_tellphone"));
		// 		CControl_bace::s_wareHouse.m_email = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"admin_email"));
		// 		CControl_bace::s_wareHouse.m_detail = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"detail"));
		// 
		// 		break;
		// 	}

		return !CControl_bace::s_userInfo.GetId().empty();

	}
}

vector<CDate_User> CControl_user::SearchList_UserInfo( CDate_search condition )
{
	vector<CDate_User> result;

	string sql = "select * from tab_user where ";
	if(!condition.m_name.IsEmpty())
		sql = sql + "user_name like '%" + m_dateChange.CStringtostring(condition.m_name) + "%' and ";
	if(!condition.m_phone.IsEmpty())
		sql = sql + "user_tellphone like '%" + m_dateChange.CStringtostring(condition.m_phone) + "%' and ";
	if(!condition.m_email.IsEmpty())
		sql = sql + "user_email like '%" + m_dateChange.CStringtostring(condition.m_email) + "%' and ";

	if(!condition.m_aBegin.IsEmpty() && !condition.m_aEnd.IsEmpty() && (condition.m_aBegin != _T("0")) && (condition.m_aEnd != _T("0")))
	{
		sql = sql + "user_age >= '" + m_dateChange.CStringtostring(condition.m_aBegin) + "' and ";
		sql = sql + "user_age <= '" + m_dateChange.CStringtostring(condition.m_aEnd) + "' and ";
	}
	if(!condition.GetKeyword().empty())
	{
		sql = sql + "( user_name like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "user_tellphone like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "user_email like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "user_age like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "detail like '%" + condition.GetKeyword() + "%'	) and ";
	}
	sql += " del_flag='0' and am_id='";
	sql += CControl_bace::s_userInfo.GetId();
	sql += "' and create_by ='";
	sql += CControl_bace::s_user.GetId();
	sql += "'";

	SQLiteStatement* stmt=g_sqlite.Statement(m_dateChange.Unicode2Utf8(sql));

	while(stmt->NextRow())
	{
		CDate_User tmp;
		tmp.SetId(stmt->ValueString (0));
		tmp.m_name         = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (2)));
		tmp.m_companyName  = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (3)));
		tmp.m_age          = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (4)));
		tmp.m_tellPhone    = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (5)));
		tmp.m_email        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (6)));
		tmp.m_detail       = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (7)));

		result.push_back(tmp);
	}
	
	return result;
}
