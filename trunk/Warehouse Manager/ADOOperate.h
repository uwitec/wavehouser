#pragma once
#include "stdafx.h"
#include <string>

using namespace std;

class CADOOperate  
{	
public:
	_ConnectionPtr	m_pConn;	// ADO����
	_CommandPtr     m_pConm;
public:	
	bool InitADOConn();		// �������ݿ�
	
	static bool ExecuteSQL(string strSql);
	static bool OpenRecordset(_RecordsetPtr &recordset,string strSQL);	//���ؼ�¼��
	static LONG64 GetRecordsCount(_RecordsetPtr &recordset,string strSQL);	//����ܼ�¼��
	static string GetCollectData(_RecordsetPtr &recordset,string name);
	static void CloseADOConn();

	static CADOOperate *InitADO();
private:

	CADOOperate();
	~CADOOperate();
	static CADOOperate *s_pADOOperate;
};

