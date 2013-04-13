#pragma once
#include "CControl_bace.h"
#include "CDate_Material.h"
class CControl_material :public CControl_bace
{
public:
	CControl_material(void);
	virtual ~CControl_material(void);

	void SetData(const CDate_Material *data);

	bool Save();
	bool Delete();
	bool Updata();
	bool Search();
private:
	CDate_Material *m_data;
};
