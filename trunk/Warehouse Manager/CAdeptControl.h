#pragma once
#include "CControl_bace.h"

enum CONTROL_TYPE{
	CONTROL_TYPE_ADMIN = 0,              //��¼�û�
	CONTROL_TYPE_USER ,                  //�û�����
	CONTROL_TYPE_COMPANY ,               //��˾��Ϣ
	CONTROL_TYPE_WATREHOUSE ,            //�ֿ���Ϣ
	CONTROL_TYPE_MATERIAL ,              //����������
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
