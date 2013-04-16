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

	_RecordsetPtr tmp;
	CADOOperate::OpenRecordset(tmp,sql);
	while(!tmp->adoEOF)
	{
		CControl_bace::s_wareHouse.SetId(CADOOperate::GetCollectData(tmp,"id"));
		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"company_name"));
		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"admin_name"));
		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"warehouse_name"));
		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"telphone"));
		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"email"));
		CControl_bace::s_wareHouse.m_name = m_dateChange.stringToCstring(CADOOperate::GetCollectData(tmp,"detail"));

		break;
	}

	return !CControl_bace::s_wareHouse.GetId().empty();
}
