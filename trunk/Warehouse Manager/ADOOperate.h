//////////////////////////////////////////////////////////////////////
// �๦�ܣ��������ݿ�Ĳ��� ��Ҫʵ�� �������ݿ� �����ݱ� ִ��SQL���
//
// jiashixiong
//////////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include <string>

using namespace std;

class CADOOperate  
{	
public:
	_ConnectionPtr	m_pConn;	// ADO����
	_RecordsetPtr	m_pRst;		// ��¼��
	_CommandPtr     m_pConm;
public:	
	bool InitADOConn();		// �������ݿ�
	bool ExecuteSQL(CString strSQL); //ִ��sql���
	_RecordsetPtr& OpenRecordset(CString strSQL);	//���ؼ�¼��
	_RecordsetPtr& GetRecordsetPtr(CString strSQL = "");
	bool BeginTrans();
	bool CommitTrans();
	bool RollbackTrans();
	LONG64 GetRecordsCount(CString strSQL);	//����ܼ�¼��
	string GetCollectData(string name);
	void CloseRecordset();
	void CloseADOConn();
	//�����˳� �Ͽ����ݿ�
	void CloseADOConnData();
	static bool ExecuteSql(CString strSql);
	static bool ReleaseCom();
	CADOOperate();
	virtual ~CADOOperate();

	static bool InitTransConnection(_ConnectionPtr &pConn,const string &dbString = "");
	static bool InitTransRecordset(_RecordsetPtr &pRecord);
	static bool OpenTransRecordset( _ConnectionPtr &pConn,_RecordsetPtr &pRecord,const string &sqlString);

private:
	static _ConnectionPtr s_pConn;
};

//#endif // !defined(AFX_ADOOPERATE_H__EB4AC016_15D4_46E9_A754_E1C1A036DAAE__INCLUDED_)
