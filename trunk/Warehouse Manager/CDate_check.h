#pragma once
#include "CDate_base.h"
#include "CDate_Class.h"
#include "CDate_Material.h"
#include "CDate_User.h"
class CDate_check:public CDate_base
{
public:
	CDate_check(void);
	~CDate_check(void);
	
public:
	int m_checkModal;

	CDate_User m_userInfo;    //人
	CDate_Class m_class;      //部门
	CDate_Material m_material;//材料名称
	CString m_operateWare;    //仓库
	int m_num;                //数量
	double m_total;
	CString m_time;           //数据
	CString m_tellPhone;      //电话
	CString m_detail;         //详细
};
