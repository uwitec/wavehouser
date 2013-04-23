#include "StdAfx.h"
#include "CControl_class.h"

CControl_class::CControl_class(void)
{
}

CControl_class::~CControl_class(void)
{
}

void CControl_class::SetData( CDate_Class *data )
{
	m_data = data;
}

bool CControl_class::Save()
{
	if(m_data->GetId().empty())
	{
		m_data->CreateId();

		string sql = "insert into tab_class values('";
		sql += m_data->GetId();
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_name);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_pName);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_contact);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_num);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_tellPhone);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_detail);
		sql += "','";
		sql += CControl_bace::s_user.GetId();
		sql += "','";
		sql += m_dateChange.GetCurTimes();
		sql +="','0')";
		//return CADOOperate::ExecuteSQL(sql);
		return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));

	}

	return Updata();
}

bool CControl_class::Delete()
{
	return false;
}

bool CControl_class::Updata()
{
	string sql = "update tab_class set class_name='";
	sql += m_dateChange.CStringtostring(m_data->m_name);
	sql += "', p_name='";
	sql += m_dateChange.CStringtostring(m_data->m_pName);
	sql += "', c_name='";
	sql += m_dateChange.CStringtostring(m_data->m_contact);
	sql += "', people_num='";
	sql += m_dateChange.CStringtostring(m_data->m_num);
	sql += "', tellphone='";
	sql += m_dateChange.CStringtostring(m_data->m_tellPhone);
	sql += "',detail='";
	sql += m_dateChange.CStringtostring(m_data->m_detail);
	sql += "',create_time='";
	sql += m_dateChange.GetCurTimes();
	sql += "',del_flag='0' where id='";
	sql += m_data->GetId();
	sql += "';";
	//return CADOOperate::ExecuteSQL(sql);
	return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
}

bool CControl_class::Search()
{
	return false;
}

vector<CDate_Class> CControl_class::SearchList_Class( CDate_search &condition )
{
	vector<CDate_Class> result;

	string sql = "select * from tab_class where ";
	if(!condition.m_name.IsEmpty())
		sql = sql + "class_name like '%" + m_dateChange.CStringtostring(condition.m_name) + "%' and ";
	if(!condition.m_cpName.IsEmpty())
		sql = sql + "p_name like '%" + m_dateChange.CStringtostring(condition.m_cpName) + "%' and ";
	if(!condition.m_coName.IsEmpty())
		sql = sql + "c_name like '%" + m_dateChange.CStringtostring(condition.m_coName) + "%' and ";
	if(!condition.m_tellPhone.IsEmpty())
		sql = sql + "tellphone like '%" + m_dateChange.CStringtostring(condition.m_tellPhone) + "%' and ";
	if(!condition.GetKeyword().empty())
	{
		sql = sql + "( class_name like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "class_name like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "p_name like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "tellphone like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "people_num like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "detail like '%" + condition.GetKeyword() + "%'	) and ";
	}
	sql += " del_flag='0' and create_by ='";
	sql += CControl_bace::s_user.GetId();
	sql += "'";

	SQLiteStatement* stmt=g_sqlite.Statement(m_dateChange.Unicode2Utf8(sql));

	while(stmt->NextRow())
	{
		CDate_Class tmp;
		tmp.SetId(stmt->ValueString (0));
		tmp.m_name         = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (1)));
		tmp.m_pName        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (2)));
		tmp.m_contact      = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (3)));
		tmp.m_num          = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (4)));
		tmp.m_tellPhone    = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (5)));
		tmp.m_detail       = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (6)));

		result.push_back(tmp);
	}
	return result;
}

CDate_Class CControl_class::Search_byId( const string &id )
{
	CDate_Class result;

	string sql = "select * from tab_class where id='";
	sql += id;
	sql += "'";

	SQLiteStatement* stmt=g_sqlite.Statement(m_dateChange.Unicode2Utf8(sql));

	while(stmt->NextRow())
	{
		result.SetId(stmt->ValueString (0));
		result.m_name         = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (1)));
		result.m_pName        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (2)));
		result.m_contact      = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (3)));
		result.m_num          = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (4)));
		result.m_tellPhone    = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (5)));
		result.m_detail       = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (6)));

		result.SetDel(stmt->ValueString (9) == "0");
	}
	return result;
}
