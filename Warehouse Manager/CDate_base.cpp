#include "StdAfx.h"
#include "CDate_base.h"
#include "uuidSet.h"
CDate_base::CDate_base(void)
{
}

CDate_base::~CDate_base(void)
{
}

bool CDate_base::CreateId()
{
	CuuidSet uuId;
	m_id = uuId.getuuid();

	return true;
}

void CDate_base::SetId( const string &id )
{
	m_id = id;
}

std::string CDate_base::GetId()
{
	return m_id;
}

void CDate_base::SetKeyword(const string &keyWord)
{
	m_keyWord = keyWord;
}

string CDate_base::GetKeyword()
{
	return m_keyWord;
}