#pragma once
#include "CDate_base.h"
class CDate_check:public CDate_base
{
public:
	CDate_check(void);
	~CDate_check(void);
	
public:
	int m_checkModal;

	CString m_operatePeople; //人
	CString m_uId;
	CString m_operateClass;  //部门
	CString m_operateWare;   //仓库
	CString m_mName;         //材料名称
	CString m_mId;
	int m_num;               //数量
	double m_total;
	CString m_time;          //数据
	CString m_tellPhone;     //电话
	CString m_detail;        //详细
};
