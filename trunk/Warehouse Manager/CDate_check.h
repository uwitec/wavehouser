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

	CDate_User m_userInfo;    //��
	CDate_Class m_class;      //����
	CDate_Material m_material;//��������
	CString m_operateWare;    //�ֿ�
	int m_num;                //����
	double m_total;
	CString m_time;           //����
	CString m_tellPhone;      //�绰
	CString m_detail;         //��ϸ
};
