#include "StdAfx.h"
#include "CControl_material.h"

CControl_material::CControl_material(void)
{
}

CControl_material::~CControl_material(void)
{
}

void CControl_material::SetData( CDate_Material *data )
{
	m_data = data;
}

bool CControl_material::Save()
{
	if(m_data->GetId().empty())
	{
		m_data->CreateId();

		string sql = "insert into tab_material values('";
		sql += m_data->GetId();
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_name);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_modal);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_manufacturer);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_unit);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_price);
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

bool CControl_material::Delete()
{
	if(m_data->GetId().empty())
		return false;

	string sql = "update tab_material set del_flag='1' where id='";
	sql += m_data->GetId();
	sql += "';";
	//return CADOOperate::ExecuteSQL(sql);
	return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
}

bool CControl_material::Updata()
{
	string sql = "update tab_material set material_name='";
	sql += m_dateChange.CStringtostring(m_data->m_name);
	sql += "', material_modal='";
	sql += m_dateChange.CStringtostring(m_data->m_modal);
	sql += "', material_manuf='";
	sql += m_dateChange.CStringtostring(m_data->m_manufacturer);
	sql += "', material_unit='";
	sql += m_dateChange.CStringtostring(m_data->m_unit);
	sql += "', material_price='";
	sql += m_dateChange.CStringtostring(m_data->m_price);
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

bool CControl_material::Search()
{
	return false;
}

vector<CDate_Material> CControl_material::SearchList_Material( CDate_search condition )
{
	vector<CDate_Material> result;

	string sql = "select * from tab_material where ";
	if(!condition.m_name.IsEmpty())
		sql = sql + "material_name like '%" + m_dateChange.CStringtostring(condition.m_name) + "%' and ";
	if(!condition.m_manufacturer.IsEmpty())
		sql = sql + "material_manuf like '%" + m_dateChange.CStringtostring(condition.m_manufacturer) + "%' and ";
	if(!condition.m_modal.IsEmpty())
		sql = sql + "material_modal like '%" + m_dateChange.CStringtostring(condition.m_modal) + "%' and ";
	if(!condition.m_price.IsEmpty())
		sql = sql + "material_price like '%" + m_dateChange.CStringtostring(condition.m_price) + "%' and ";
	if(!condition.m_unit.IsEmpty())
		sql = sql + "material_unit like '%" + m_dateChange.CStringtostring(condition.m_unit) + "%' and ";
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
		CDate_Material tmp;
		tmp.SetId(stmt->ValueString (0));
		tmp.m_name         = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (1)));
		tmp.m_modal        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (2)));
		tmp.m_manufacturer = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (3)));
		tmp.m_unit         = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (4)));
		tmp.m_price        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (5)));
		tmp.m_detail       = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (6)));

		result.push_back(tmp);
	}
	return result;
}

CDate_Material CControl_material::Search_byId( const string &id )
{
	CDate_Material result;
	string sql = "select * from tab_material where id='";
	sql += id;
	sql += "'";

	SQLiteStatement* stmt=g_sqlite.Statement(sql);

	while(stmt->NextRow())
	{
		result.SetId(stmt->ValueString (0));
		result.m_name         = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (1)));
		result.m_modal        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (2)));
		result.m_manufacturer = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (3)));
		result.m_unit         = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (4)));
		result.m_price        = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (5)));
		result.m_detail       = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (6)));

		break;
	}

	return result;

}
