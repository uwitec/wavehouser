#pragma once
#include "CDate_base.h"
class CDate_check:public CDate_base
{
public:
	CDate_check(void);
	~CDate_check(void);
	
public:
	int m_checkModal;

	CString m_operatePeople; //��
	CString m_uId;
	CString m_operateClass;  //����
	CString m_operateWare;   //�ֿ�
	CString m_mName;         //��������
	CString m_mId;
	int m_num;               //����
	double m_total;
	CString m_time;          //����
	CString m_tellPhone;     //�绰
	CString m_detail;        //��ϸ
};
