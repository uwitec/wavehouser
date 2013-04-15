//////////////////////////////////////////////////////////////////////
// 类功能：用于数据库的操作 主要实现 连接数据库 读数据表 执行SQL语句
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
	_ConnectionPtr	m_pConn;	// ADO连接
	_RecordsetPtr	m_pRst;		// 记录集
	_CommandPtr     m_pConm;
public:	
	bool InitADOConn();		// 连接数据库
	bool ExecuteSQL(CString strSQL); //执行sql语句
	_RecordsetPtr& OpenRecordset(CString strSQL);	//返回记录集
	_RecordsetPtr& GetRecordsetPtr(CString strSQL = "");
	bool BeginTrans();
	bool CommitTrans();
	bool RollbackTrans();
	LONG64 GetRecordsCount(CString strSQL);	//获得总记录数
	string GetCollectData(string name);
	void CloseRecordset();
	void CloseADOConn();
	//程序退出 断开数据库
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
