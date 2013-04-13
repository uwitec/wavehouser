#pragma once
#include "CControl_bace.h"
#include "CDate_Warehouse.h"
class CControl_warehouse :public CControl_bace
{
public:
	CControl_warehouse(void);
	virtual ~CControl_warehouse(void);

	void SetData(const CDate_warehouse *data);

	bool Save();
	bool Delete();
	bool Updata();
	bool Search();
private:
	CDate_warehouse *m_data;
};
