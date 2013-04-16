#include "StdAfx.h"
#include "CControl_warehouse.h"
#include "CControl_DB.h"
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

		string sql = "insert into tab_warehouse value('";
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
		sql +="')";
		return CADOOperate::ExecuteSQL(sql);
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
	sql += "', telphone='";
	sql += m_dateChange.CStringtostring(m_data->m_tell);
	sql += "', email='";
	sql += m_dateChange.CStringtostring(m_data->m_email);
	sql += "',detail='";
	sql += m_dateChange.CStringtostring(m_data->m_detail);
	sql += "',create_time='";
	sql += m_dateChange.GetCurTimes();
	sql +="' where id='";
	sql += m_data->GetId();
	sql += "';";
	return CADOOperate::ExecuteSQL(sql);
}

bool CControl_warehouse::Search()
{
	string sql = "select * from tab_warehouse where create_by='";
	sql += CControl_bace::s_user.GetId();
	sql += "'";

	_RecordsetPtr tmp;
	CADOOperate::OpenRecordset(tmp,sql);
	while(!tmp->adoEOF)
	{
		CControl_bace::s_wareHouse.SetId(CADOOperate::GetCollectData(tmp,"id"));
		CControl_bace::s_wareHouse.m_cname = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"company_name"));
		CControl_bace::s_wareHouse.m_aname = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"admin_name"));
		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"warehouse_name"));
		CControl_bace::s_wareHouse.m_tell = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"telphone"));
		CControl_bace::s_wareHouse.m_email = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"email"));
		CControl_bace::s_wareHouse.m_detail = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"detail"));

		break;
	}

	return !CControl_bace::s_wareHouse.GetId().empty();
}
