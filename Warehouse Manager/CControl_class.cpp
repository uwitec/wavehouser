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

bool CControl_class::Delete()
{
	return false;
}

bool CControl_class::Updata()
{
	return false;
}

bool CControl_class::Search()
{
	return false;
}

vector<CDate_Class> CControl_class::SearchList_Class( const CDate_search &condition )
{
	vector<CDate_Class> result;

	string sql = "select * from tab_class where ";
// 	if(!condition.m_name.IsEmpty())
// 		sql = sql + "material_name like '%" + m_dateChange.CStringtostring(condition.m_name) + "%' and ";
// 	if(!condition.m_manufacturer.IsEmpty())
// 		sql = sql + "material_manuf like '%" + m_dateChange.CStringtostring(condition.m_manufacturer) + "%' and ";
// 	if(!condition.m_modal.IsEmpty())
// 		sql = sql + "material_modal like '%" + m_dateChange.CStringtostring(condition.m_modal) + "%' and ";
// 	if(!condition.m_price.IsEmpty())
// 		sql = sql + "material_price like '%" + m_dateChange.CStringtostring(condition.m_price) + "%' and ";
// 	if(!condition.m_unit.IsEmpty())
// 		sql = sql + "material_unit like '%" + m_dateChange.CStringtostring(condition.m_unit) + "%' and ";
// 	if(!condition.GetKeyword().empty())
// 	{
// 		sql = sql + "( material_name like '%" + condition.GetKeyword() + "%' or ";
// 		sql = sql + "material_modal like '%" + condition.GetKeyword() + "%' or ";
// 		sql = sql + "material_manuf like '%" + condition.GetKeyword() + "%' or ";
// 		sql = sql + "material_price like '%" + condition.GetKeyword() + "%' or ";
// 		sql = sql + "material_unit like '%" + condition.GetKeyword() + "%' or ";
// 		sql = sql + "detail like '%" + condition.GetKeyword() + "%'	) and ";
// 	}
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

	}
	return result;
}
