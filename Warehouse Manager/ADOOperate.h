#pragma once
#include "stdafx.h"
#include <string>

using namespace std;

class CADOOperate  
{	
public:
	_ConnectionPtr	m_pConn;	// ADO连接
	_CommandPtr     m_pConm;
public:	
	bool InitADOConn();		// 连接数据库
	
	static bool ExecuteSQL(string strSql);
	static bool OpenRecordset(_RecordsetPtr &recordset,string strSQL);	//返回记录集
	static LONG64 GetRecordsCount(_RecordsetPtr &recordset,string strSQL);	//获得总记录数
	static string GetCollectData(_RecordsetPtr &recordset,string name);
	static void CloseADOConn();

	static CADOOperate *InitADO();
private:

	CADOOperate();
	~CADOOperate();
	static CADOOperate *s_pADOOperate;
};

