#include "StdAfx.h"
#include "CControl_company.h"

CControl_company::CControl_company(void)
{
}

CControl_company::~CControl_company(void)
{
}

void CControl_company::SetData( const CDate_Company *data )
{
	//m_data = data;
}

bool CControl_company::Save()
{
	return false;
}

bool CControl_company::Delete()
{
	return false;
}

bool CControl_company::Updata()
{
	return false;
}

bool CControl_company::Search()
{
	string sql = "select * from tab_warehouse where create_by='";
	sql += CControl_bace::s_user.GetId();
	sql += "'";

	SQLiteStatement* stmt=g_sqlite.Statement(sql);

	while(stmt->NextRow())
	{
		CControl_bace::s_company.SetId(stmt->ValueString (0));
		CControl_bace::s_company.m_companyName  = m_dateChange.stringToCstring(stmt->ValueString (1));
		CControl_bace::s_company.m_wareName  = m_dateChange.stringToCstring(stmt->ValueString (2));
		CControl_bace::s_company.m_wareId   = m_dateChange.stringToCstring(stmt->ValueString (3));
		CControl_bace::s_company.m_address   = m_dateChange.stringToCstring(stmt->ValueString (4));
		CControl_bace::s_company.m_tellPhone  = m_dateChange.stringToCstring(stmt->ValueString (5));
		CControl_bace::s_company.m_tellMan  = m_dateChange.stringToCstring(stmt->ValueString (5));
		CControl_bace::s_company.m_detail = m_dateChange.stringToCstring(stmt->ValueString (6));

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

	return !CControl_bace::s_wareHouse.GetId().empty();
}
