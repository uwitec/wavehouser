#include "StdAfx.h"
#include "CData_bace.h"
#include "uuidSet.h"
CData_bace::CData_bace(void)
{
	CreateId();
}

CData_bace::~CData_bace(void)
{
}

bool CData_bace::CreateId()
{
	CuuidSet uuId;
	m_id = uuId.getuuid();

	return true;
}

void CData_bace::SetId( const string &id )
{
	m_id = id;
}

std::string CData_bace::GetId()
{
	return m_id;
}
