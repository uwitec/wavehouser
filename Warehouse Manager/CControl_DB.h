#pragma once

#include <string>

using namespace std;

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF") rename("BOF","adoBOF")

class CControl_DB
{
public:
	CControl_DB(void);
	~CControl_DB(void);

	bool InitDB();

	_ConnectionPtr	m_pConn;	// ADO����
	_RecordsetPtr	m_pRst;		// ��¼��
public:	
	bool InitADOConn();		// �������ݿ�
	bool ExecuteSQL(string strSQL); //ִ��sql���
	_RecordsetPtr& OpenRecordset(string strSQL);	//���ؼ�¼��
	LONG64 GetRecordsCount(string strSQL);	//����ܼ�¼��
	string GetCollectData(string name);
	void CloseRecordset();
	void CloseADOConn();
	//�����˳� �Ͽ����ݿ�
	void CloseADOConnData();
};
