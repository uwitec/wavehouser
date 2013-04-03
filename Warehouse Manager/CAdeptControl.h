#pragma once
#include "CControl_bace.h"

enum CONTROL_TYPE{
	CONTROL_TYPE_ADMIN = 0,              //登录用户
	CONTROL_TYPE_USER ,                  //用户资料
	CONTROL_TYPE_COMPANY ,               //公司信息
	CONTROL_TYPE_WATREHOUSE ,            //仓库信息
	CONTROL_TYPE_MATERIAL ,              //材料嘻嘻你
	CONTROL_TYPE_OUTHER
};


class CAdeptControl
{
public:
	CAdeptControl(const CONTROL_TYPE &type);
	~CAdeptControl(void);


private:
	CControl_bace *m_control;
};
