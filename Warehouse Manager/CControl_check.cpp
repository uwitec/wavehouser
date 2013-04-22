#include "StdAfx.h"
#include "CControl_check.h"

CControl_check::CControl_check(void)
{
}

CControl_check::~CControl_check(void)
{
}

void CControl_check::SetData( CDate_check *data )
{
	m_data = data;
}

bool CControl_check::Save()
{
	if(m_data->GetId().empty())
	{
		m_data->CreateId();

		string sql = "insert into tab_check values('";
		sql += m_data->GetId();
		sql += "','";
		sql += m_data->m_userInfo.GetId();
		sql += "','";
		sql += m_data->m_material.GetId();
		sql += "','";
		sql += m_data->m_class.GetId();
		sql += "','";
		sql += CControl_bace::s_wareHouse.GetId();
		sql += "','";
		sql += m_data->m_checkModal == 1 ? "1":"0";
		sql += "','";
		char cTmp[20] = {0};
		itoa(m_data->m_num,cTmp,10);
		sql += cTmp;
		sql += "','";

		memset(cTmp,0,20);
		ltoa(m_data->m_total,cTmp,10);

		sql += cTmp;
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

bool CControl_check::Delete()
{
	if(m_data->GetId().empty())
		return false;

	string sql = "update tab_check set del_flag='1' where id='";
	sql += m_data->GetId();
	sql += "';";
	//return CADOOperate::ExecuteSQL(sql);
	return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
}

bool CControl_check::Updata()
{
	string sql = "update tab_check set u_id='";
	sql += m_data->m_userInfo.GetId();
	sql += "', m_id='";
	sql += m_data->m_material.GetId();
	sql += "', c_id='";
	sql += m_data->m_class.GetId();
	sql += "', w_id='";
	sql += CControl_bace::s_wareHouse.GetId();
	sql += "', num='";
	char cTmp[20] = {0};
	itoa(m_data->m_num,cTmp,10);
	sql += (string)cTmp;

	sql += "', total='";
	memset(cTmp,0,20);
	ltoa(m_data->m_total,cTmp,10);
	sql += (string)cTmp;

	sql += "', tellphone='";
	sql += m_dateChange.CStringtostring(m_data->m_tellPhone);
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

bool CControl_check::Search()
{
	return false;
}

vector<CDate_check> CControl_check::SearchList_Check( CDate_search condition )
{
	vector<CDate_check> result;

	string sql = "select * from tab_check where ";
	if(!condition.m_name.IsEmpty())
		sql = sql + "u_id ='" + m_dateChange.CStringtostring(condition.m_name) + "' and ";
	if(!condition.m_name.IsEmpty())
		sql = sql + "c_id ='" + m_dateChange.CStringtostring(condition.m_name) + "' and ";
	if(!condition.GetKeyword().empty())
	{
		sql = sql + "( material_name like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "material_modal like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "material_manuf like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "material_price like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "material_unit like '%" + condition.GetKeyword() + "%' or ";
		sql = sql + "detail like '%" + condition.GetKeyword() + "%'	) and ";
	}
	sql += " del_flag='0' and create_by ='";
	sql += CControl_bace::s_user.GetId();
	sql += "'";

	SQLiteStatement* stmt=g_sqlite.Statement(m_dateChange.Unicode2Utf8(sql));

	while(stmt->NextRow())
	{
		CDate_check tmp;
		tmp.SetId(stmt->ValueString (0));
// 		tmp.m_name         = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (1)));
// 		tmp.m_modal        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (2)));
// 		tmp.m_manufacturer = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (3)));
// 		tmp.m_unit         = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (4)));
// 		tmp.m_price        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (5)));
		tmp.m_detail       = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (6)));

		result.push_back(tmp);
	}
	return result;
}
