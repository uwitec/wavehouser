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

	_ConnectionPtr	m_pConn;	// ADO连接
	_RecordsetPtr	m_pRst;		// 记录集
public:	
	bool InitADOConn();		// 连接数据库
	bool ExecuteSQL(string strSQL); //执行sql语句
	_RecordsetPtr& OpenRecordset(string strSQL);	//返回记录集
	LONG64 GetRecordsCount(string strSQL);	//获得总记录数
	string GetCollectData(string name);
	void CloseRecordset();
	void CloseADOConn();
	//程序退出 断开数据库
	void CloseADOConnData();
};
