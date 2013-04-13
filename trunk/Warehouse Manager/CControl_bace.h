#pragma once
#include "CControl_DB.h"
#include "CDate_base.h"
class CControl_bace
{
public:
	CControl_bace(void);
	~CControl_bace(void);

	virtual void SetData(const CDate_base *data);

	virtual bool Save();
	virtual bool Delete();
	virtual bool Updata();
	virtual bool Search();
private:
	CDate_base *m_data;
};
