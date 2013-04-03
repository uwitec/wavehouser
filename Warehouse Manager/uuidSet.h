/************************************************************************/
/* ´´½¨uu
   filename:uuidSet.h
   createby:liu   time:2010-10-24
/************************************************************************/
#pragma once
#include "stdafx.h"
#include <ObjBase.h>
#include <string>

using namespace std;
class CuuidSet
{
public:
	CuuidSet()
	{
	}
	~CuuidSet()
	{
	}

	string getuuid()
	{
		CoCreateGuid(&m_uuid);
		char buf[64] = {0};
		_snprintf(
			buf,
			sizeof(buf),
			"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			m_uuid.Data1, m_uuid.Data2, m_uuid.Data3,
			m_uuid.Data4[0], m_uuid.Data4[1],
			m_uuid.Data4[2], m_uuid.Data4[3],
			m_uuid.Data4[4], m_uuid.Data4[5],
			m_uuid.Data4[6], m_uuid.Data4[7]);
		return std::string(buf);
	}
	
	
private:
	GUID  m_uuid;
};