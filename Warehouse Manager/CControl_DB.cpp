#include "StdAfx.h"
#include "CControl_DB.h"

CControl_DB::CControl_DB(void)
{
	m_pConn = NULL;
	m_pRst  = NULL;
}

CControl_DB::~CControl_DB(void)
{
	CoUninitialize();     // 卸载COM库
}

bool CControl_DB::InitDB()
{
// 	CoInitialize(NULL);	                             //初始化Com组件
// 	_ConnectionPtr conPtr;	                         //数据库链接指针
// 
// 	conPtr.CreateInstance(__uuidof(Connection));	 //Connection用于与数据库服务器的链接另一种方式
// 	// MySQL ODBC 5.1 Driver为驱动名称（取决于我们为MySql安装的驱动），localhost为服务器地址，test为数据库名，root为用户名（MySql默认用户名为root），sa为密码
// 	CString conStr=_T("Driver={ MySQL ODBC 5.1 Driver };Server= localhost;Database=test;");
// 	/******************连接数据库********************/
// 	try
// 	{
// 		conPtr->ConnectionTimeout = 50;	 //设置连接时间
// 		conPtr->Open((_bstr_t)conStr, "root","haipe", adModeUnknown);
// 	}
// 	catch(_com_error e)	 //捕捉异常
// 	{
// 		AfxMessageBox(e.ErrorMessage());
// 	} 
// 	CoUninitialize();	 //释放com组件

	return false;
}

//*********************************************
//ADO组件连接数据库
//*********************************************
bool CControl_DB::InitADOConn()
{	
	bool result = false;
	try
	{
		::CoInitialize(NULL);
		HRESULT flag = m_pConn.CreateInstance(_T("ADODB.Connection"));  //创建连接对象实例
		if(SUCCEEDED(flag)) 
		{
			_bstr_t strConnect="Driver={ MySQL ODBC 5.1 Driver };Server= localhost;Database=warehouse_db;";

			result = SUCCEEDED(m_pConn->Open(strConnect, "root","haipe", adModeUnknown)); //打开数据库
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //弹出错误处理

		result = false;
	}
	catch (...)
	{
		//AfxMessageBox(L"SYS Error");
		result = false;
	}

	return result;
}

//*********************************************
//ADO组件获取记录集
//*********************************************
_RecordsetPtr&  CControl_DB::OpenRecordset(string strSQL)
{
	try
	{
		if(m_pConn==0x00000000)	                        // 判断连接是否断开
		{
			m_pConn=NULL;
			if(InitADOConn())	                        // 重新连接
			{

			}
		}
		m_pRst.CreateInstance("ADODB.Recordset");		//创建记录集对象实例
		m_pRst->raw_Close();                            // 关闭记录集
		m_pRst->Open((_bstr_t)strSQL.c_str(),m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

	return m_pRst;	// 返回记录集
}

//*********************************************
//关闭记录集
//*********************************************
void CControl_DB::CloseRecordset()
{
	if(m_pRst->State)
	{
		m_pRst->Close();
	}
	m_pRst = NULL;
}

//*********************************************
//关闭与ADO组件的连接，关闭数据库连接
//*********************************************
void CControl_DB::CloseADOConn()
{	
	if (m_pConn != NULL)
	{
		if (m_pConn->State)
		{
			m_pConn->Close();
		}
	}
	m_pConn = NULL;
	
}
//*********************************************
//执行增删改sql语句
//*********************************************
bool CControl_DB::ExecuteSQL(string strSQL)
{	
	try
	{
		if(m_pConn==0x00000000)		// 判断连接是否断开
		{
			m_pConn=NULL;
			InitADOConn();		// 重新连接
		}

		return SUCCEEDED(m_pConn->Execute((_bstr_t)strSQL.c_str(),&vtMissing,0));
	}
	catch(_com_error e)
	{
		//AfxMessageBox(e.Description());
		return false;
	}
	return false;
}

//*******************************************
//获取总记录条数
//*******************************************

LONG64 CControl_DB::GetRecordsCount(string strSQL)
{
	LONG64 count;
	try
	{
		if(m_pConn==0X00000000)		// 判断连接是否断开
			InitADOConn();		// 重新连接

		m_pRst.CreateInstance(_T("ADODB.Recordset"));//__uuidof(Recordset));		//创建记录集对象实例
		m_pRst->raw_Close();	// 关闭记录集
		m_pRst->Open((_bstr_t)strSQL.c_str(),m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		//AfxMessageBox(e.Description());
		count = 0;
	}

	count =atoi((char*)(_bstr_t)m_pRst->GetCollect("count")) ;

	return count;	// 返回记录总数
}

/************************************************************************/
/* 获取每个字段的值，并做处理。                                                                     */
/************************************************************************/
std::string CControl_DB::GetCollectData( string name )throw(_com_error)
{
	string val;

	_variant_t var = m_pRst->GetCollect((_bstr_t)(char *)name.c_str());
	if(var.vt != VT_NULL)
	val = (string)_bstr_t(var);
	return val;
}
void CControl_DB::CloseADOConnData()
{
	CloseADOConn();
}

