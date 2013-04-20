#include "StdAfx.h"
#include "CControl_warehouse.h"
//#include "CControl_DB.h"
CControl_warehouse::CControl_warehouse(void)
{
}

CControl_warehouse::~CControl_warehouse(void)
{
}

void CControl_warehouse::SetData( CDate_warehouse *data )
{
	m_data = data;
}

bool CControl_warehouse::Save()
{
	if(CControl_bace::s_user.GetId().empty() || CControl_bace::s_wareHouse.GetId().empty())
	{
		if(CControl_bace::s_wareHouse.GetId().empty())
			m_data->CreateId();
		else
			m_data->SetId(CControl_bace::s_wareHouse.GetId());

		string sql = "insert into tab_warehouse values('";
		sql += m_data->GetId();
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_cname);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_aname);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_name);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_tell);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_email);
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
	else
	{
		return Updata();
	}
}

bool CControl_warehouse::Delete()
{
	return false;
}

bool CControl_warehouse::Updata()
{
	string sql = "update tab_warehouse set company_name='";
	sql += m_dateChange.CStringtostring(m_data->m_cname);
	sql += "', admin_name='";
	sql += m_dateChange.CStringtostring(m_data->m_aname);
	sql += "', warehouse_name='";
	sql += m_dateChange.CStringtostring(m_data->m_name);
	sql += "', admin_tellphone='";
	sql += m_dateChange.CStringtostring(m_data->m_tell);
	sql += "', admin_email='";
	sql += m_dateChange.CStringtostring(m_data->m_email);
	sql += "',detail='";
	sql += m_dateChange.CStringtostring(m_data->m_detail);
	sql += "',create_time='";
	sql += m_dateChange.GetCurTimes();
	sql +="' where id='";
	sql += CControl_bace::s_wareHouse.GetId();
	sql += "';";
	//return CADOOperate::ExecuteSQL(sql);
	return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
}

bool CControl_warehouse::Search()
{
	string sql = "select * from tab_warehouse where create_by='";
	sql += CControl_bace::s_user.GetId();
	sql += "'";

	SQLiteStatement* stmt=g_sqlite.Statement(sql);

	while(stmt->NextRow())
	{
		CControl_bace::s_wareHouse.SetId(stmt->ValueString (0));
		CControl_bace::s_wareHouse.m_cname  = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (1)));
		CControl_bace::s_wareHouse.m_aname  = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (2)));
		CControl_bace::s_wareHouse.m_name   = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (3)));
		CControl_bace::s_wareHouse.m_tell   = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (4)));
		CControl_bace::s_wareHouse.m_email  = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (5)));
		CControl_bace::s_wareHouse.m_detail = m_dateChange.stringToCstring(m_dateChange.Utf82Unicode(stmt->ValueString (6)));

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

	return !CControl_bace::s_wareHouse.GetId().empty();
}
