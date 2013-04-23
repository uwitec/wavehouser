#pragma once
#include "stdafx.h"
#include "CDate_User.h"
#include "CDate_Material.h"
#include "CDate_check.h"
#include "CDate_Class.h"
class CControl_Export
{
public:
	CControl_Export(void);
	~CControl_Export(void);

	static bool ExportUser(const vector<CDate_User> &dates);
	static bool ExportMaterial(const vector<CDate_Material> &dates);
	static bool ExportCheck(const vector<CDate_check> &dates);
	static bool ExportClass(const vector<CDate_Class > &dates);
};
