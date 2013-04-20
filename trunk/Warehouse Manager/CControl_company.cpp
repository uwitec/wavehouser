#include "StdAfx.h"
#include "CControl_company.h"

CControl_company::CControl_company(void)
{
}

CControl_company::~CControl_company(void)
{
}

void CControl_company::SetData( CDate_Company *data )
{
	m_data = data;
}

bool CControl_company::Save()
{
	if(CControl_bace::s_user.GetId().empty() || CControl_bace::s_company.GetId().empty())
	{
		if(CControl_bace::s_company.GetId().empty())
			m_data->CreateId();
		else
			m_data->SetId(CControl_bace::s_company.GetId());

		string sql = "insert into tab_company values('";
		sql += m_data->GetId();
		sql += "','";
		sql += CControl_bace::s_user.GetId();
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_companyName);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_address);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_tellPhone);
		sql += "','";
		sql += m_dateChange.CStringtostring(m_data->m_tellMan);
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

bool CControl_company::Delete()
{
	return false;
}

bool CControl_company::Updata()
{
	string sql = "update tab_company set company_name='";
	sql += m_dateChange.CStringtostring(m_data->m_companyName);
	sql += "', compant_address='";
	sql += m_dateChange.CStringtostring(m_data->m_address);
	sql += "', company_tellphone='";
	sql += m_dateChange.CStringtostring(m_data->m_tellPhone);
	sql += "', company_contact='";
	sql += m_dateChange.CStringtostring(m_data->m_tellMan);
	sql += "',detail='";
	sql += m_dateChange.CStringtostring(m_data->m_detail);
	sql += "',create_time='";
	sql += m_dateChange.GetCurTimes();
	sql +="' where id='";
	sql += CControl_bace::s_company.GetId();
	sql += "';";
	//return CADOOperate::ExecuteSQL(sql);
	return g_sqlite.DirectStatement(m_dateChange.Unicode2Utf8(sql));
}

bool CControl_company::Search()
{
	string sql = "select * from tab_company where create_by='";
	sql += CControl_bace::s_user.GetId();
	sql += "'";

	SQLiteStatement* stmt=g_sqlite.Statement(sql);

	CControl_bace::s_company.m_wareName    = CControl_bace::s_wareHouse.m_name;

	while(stmt->NextRow())
	{
		CControl_bace::s_company.SetId(stmt->ValueString (0));
		CControl_bace::s_company.m_wareId      = m_dateChange.stringToCstring(stmt->ValueString (1));
		CControl_bace::s_company.m_companyName = m_dateChange.stringToCstring(stmt->ValueString (2));
		CControl_bace::s_company.m_address     = m_dateChange.stringToCstring(stmt->ValueString (3));
		CControl_bace::s_company.m_tellPhone   = m_dateChange.stringToCstring(stmt->ValueString (4));
		CControl_bace::s_company.m_tellMan     = m_dateChange.stringToCstring(stmt->ValueString (5));
		CControl_bace::s_company.m_detail      = m_dateChange.stringToCstring(stmt->ValueString (6));

		break;
	}

// 	_RecordsetPtr tmp;
// 	CADOOperate::OpenRecordset(tmp,sql);
// 	while(!tmp->adoEOF)
// 	{
// 		CControl_bace::s_wareHouse.SetId(CADOOperate::GetCollectData(tmp,"id"));
// 		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"company_name"));
// 		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"admin_name"));
// 		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"warehouse_name"));
// 		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"telphone"));
// 		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"email"));
// 		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"detail"));
// 
// 		break;
// 	}

	return !CControl_bace::s_company.GetId().empty();
}
