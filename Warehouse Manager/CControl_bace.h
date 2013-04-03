#pragma once
#include "CControl_DB.h"
#include "CData_bace.h"
class CControl_bace
{
public:
	CControl_bace(void);
	~CControl_bace(void);

	virtual void SetData(const CData_bace *data);

	virtual bool Save();
	virtual bool Delete();
	virtual bool Updata();
	virtual bool Search();
private:
	CData_bace *m_data;
};
