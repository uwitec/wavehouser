#pragma once
#include <string>

using namespace std;
class CDate_base
{
public:
	CDate_base(void);
	~CDate_base(void);

	bool CreateId();

	void SetId(const string &id);
	string GetId();

	void SetKeyword(const string &keyWord);
	string GetKeyword();
private:
	string m_id;
	string m_keyWord;
};

class CDate_search : public CDate_base
{
public:
	CDate_search(){};
	~CDate_search(){};

	CString m_name;
	CString m_modal;       //�ͺ�
	CString m_manufacturer;//��������
	CString m_unit;
	CString m_price;

	CString m_checkModal;
	CString m_class;//����
	CString m_pName;//��Ա
	CString m_tBegin;
	CString m_tEnd;

	CString m_phone;
	CString m_aBegin;
	CString m_aEnd;
	CString m_email;

};