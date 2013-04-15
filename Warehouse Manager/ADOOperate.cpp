// ADOOperate.cpp: implementation of the CADOOperate class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ADOOperate.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

_ConnectionPtr CADOOperate::s_pConn = NULL;
CADOOperate::CADOOperate()
{
	m_pConn=NULL;
}

CADOOperate::~CADOOperate()
{
	CoUninitialize();	// 卸载COM库
}

//*********************************************
//ADO组件连接数据库
//jiashixiong  
//*********************************************
bool CADOOperate::InitADOConn()
{	
	
	try
	{
		::CoInitialize(NULL);
		HRESULT hr=m_pConn.CreateInstance(_T("ADODB.Connection"));  //创建连接对象实例
		if(SUCCEEDED(hr)) 
		{
			//_bstr_t strConnect="DRIVER={SQLite3 ODBC Driver};\uid=;pwd=;DBQ=jo_db_local.db;";
			_bstr_t strConnect="Driver=SQLite3 ODBC Driver;Database=jo_db_local.db";
			//m_pConn->ConnectionString=strConnect;
			m_pConn->Open(strConnect,_T(""),_T(""),adModeUnknown); //打开数据库

			if(m_pConm == NULL)
				m_pConm.CreateInstance(_T("ADODB.Command"));
				//m_pConm.CreateInstance(__uuidof(Command));
		}
		else
		{
			CMyBox::Show(_T("创建连接数据库对象实例失败!"));
		}

	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("数据库连接失败!"));
		//AfxMessageBox(e.Description()); //弹出错误处理
		return false;
	}
	catch (...)
	{
		//AfxMessageBox(L"SYS Error");
		return false;
	}

	return true;
}

//*********************************************
//ADO组件获取记录集
//jiashixiong  
//*********************************************
_RecordsetPtr&  CADOOperate::OpenRecordset(CString strSQL)
{
	//ASSERT(!strSQL.IsEmpty());										//SQL语句不能为空

	try
	{
		if(m_pConn==0x00000000)		// 判断连接是否断开
		{
			m_pConn=NULL;
			InitADOConn();		// 重新连接
		}
		m_pRst.CreateInstance("ADODB.Recordset");		//创建记录集对象实例
		m_pRst->raw_Close();	// 关闭记录集
		m_pRst->Open((_bstr_t)strSQL,m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		
	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("记录集打开失败！"));
		//AfxMessageBox(e.Description());

	}

	return m_pRst;	// 返回记录集
}

_RecordsetPtr& CADOOperate::GetRecordsetPtr(CString strSQL)
{
	try
	{
		if(m_pConn==0x00000000)		// 判断连接是否断开
		{
			m_pConn=NULL;
			InitADOConn();		// 重新连接
		}

		if(!strSQL.IsEmpty())
		{
			m_pRst.CreateInstance("ADODB.Recordset");		//创建记录集对象实例
			m_pRst->raw_Close();	// 关闭记录集
			m_pRst->Open((_bstr_t)strSQL,m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		}
	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("记录集打开失败！"));
		//AfxMessageBox(e.Description());

	}

	return m_pRst;
}
//*********************************************
//关闭记录集
//jiashixiong
//*********************************************
void CADOOperate::CloseRecordset()
{
	if(m_pRst->State)
	{
		m_pRst->Close();
	}
	m_pRst = NULL;
}

//*********************************************
//关闭与ADO组件的连接，关闭数据库连接
//jiashixiong
//*********************************************
void CADOOperate::CloseADOConn()
{	
	if (m_pConn != NULL)
	{
		if (m_pConn->State)
		{
			m_pConn->Close();
		}
	}
	m_pConn = NULL;
	//	错误说明：智能指针_RecordsetPtr和_ConnectionPtr在超出作用域是会自动释放的，
	//  也就是说指针在CreateInstance()的时候分配内存，在作用域外释放，
	//  所以自己调用Release()并不是必需的，不过调用有可能出错，而设为NULL是完全可以不用的。 
	//	m_pConn->Release();
	
}
//*********************************************
//执行增删改sql语句
//jiashixiong
//*********************************************
bool CADOOperate::ExecuteSQL(CString strSQL)
{	
	try
	{
		if(m_pConn==0x00000000)		// 判断连接是否断开
		{
			m_pConn=NULL;
			InitADOConn();		// 重新连接
		}

		//m_pConn->Execute((_bstr_t)strSQL,&vtMissing,0);
		//m_pRst.CreateInstance(__uuidof(Recordset));		//创建记录集对象实例
		//m_pRst->raw_Close();	// 关闭记录集
		//m_pRst->Open((_bstr_t)strSQL,m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		m_pConm->ActiveConnection = m_pConn;
		m_pConm->CommandType = adCmdText;
		m_pConm->CommandText = _bstr_t(strSQL);

		_variant_t vNull;
		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;

		m_pConm->Execute(&vNull, &vNull, adCmdText);
	}
	catch(_com_error e)
	{
		//AfxMessageBox(e.Description());
		return false;
	}

	return true;	// 返回记录集
}

//*******************************************
//获取总记录条数
//*******************************************

LONG64 CADOOperate::GetRecordsCount(CString strSQL)
{
	LONG64 count;
	try
	{
		if(m_pConn==0X00000000)		// 判断连接是否断开
			InitADOConn();		// 重新连接

		m_pRst.CreateInstance(_T("ADODB.Recordset"));//__uuidof(Recordset));		//创建记录集对象实例
		m_pRst->raw_Close();	// 关闭记录集
		m_pRst->Open((_bstr_t)strSQL,m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		//AfxMessageBox(e.Description());
		count = 0;
	}

	//只取第一条记录
	//while(!m_pRst->adoEOF)
	//{
	count =atoi((char*)(_bstr_t)m_pRst->GetCollect("count")) ;
	//	m_pRst->MoveNext();//将记录集指针移动到下一条记录
	//}

	return count;	// 返回记录总数
}

/************************************************************************/
/* 获取每个字段的值，并做处理。                                                                     */
/************************************************************************/
std::string CADOOperate::GetCollectData( string name )throw(_com_error)
{
	string val;
// 	try
// 	{
// 		_variant_t var = m_pRst->GetCollect((_bstr_t)(char *)name.c_str());
// 		if(var.vt != VT_NULL)
// 			val = (string)_bstr_t(var);
// 
// 	}
// 	catch(_com_error *e)
// 	{
// 		//AfxMessageBox(e->ErrorMessage());
// 	}

	_variant_t vars = "有两年半的工作经验,主要从事.NET\JAVA的WEB开发,对保险业务、移动业务开发有一定的工作经验,熟练.NET三层架构开发,Spring的MVC开发,熟悉使用jquery,无刷新技术,熟练使用ORACLE\SQL2000\SQL2005数据库,精通数据库存储过程编写,熟练掌握oracle数据库高级队列、JOB等,在数据库设计方面有一定的工作经验。熟悉.NET\JAVA对AD、Exchange的操作,熟悉IIS发布。在近几个项目开发中都担任重要角色,如技术难点的攻破、核心业务模块的编写、组员工作任务分配等等,具备一定与客户的需求沟通能力。 可经常出差。";

	_variant_t var = m_pRst->GetCollect((_bstr_t)(char *)name.c_str());
	//m_pRst->get_Collect((_bstr_t)(char *)name.c_str(),&var);
	//m_pRst->GetFields().value;
	if(var.vt != VT_NULL)
		val = (string)_bstr_t(var);
// 	if((m_pRst->GetCollect((_bstr_t)(char *)name.c_str()).vt) != VT_NULL)
// 		val = (string)_bstr_t(m_pRst->GetCollect((_bstr_t)(char *)name.c_str()));
	return val;
}
void CADOOperate::CloseADOConnData()
{
	CloseADOConn();
}

bool CADOOperate::BeginTrans()
{
	try
	{
		if(m_pConn == 0x00000000)		// 判断连接是否断开
		{
			return false;
		}

		m_pConn->BeginTrans();
	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("事务建立失败！"));

		return false;
	}

	return true;
}

bool CADOOperate::CommitTrans()
{
	try
	{
		if(m_pConn == 0x00000000)		// 判断连接是否断开
		{
			return false;
		}

		m_pConn->CommitTrans();
	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("事务提交失败！"));

		return false;
	}

	return true;
}

bool CADOOperate::RollbackTrans()
{
	try
	{
		if(m_pConn == 0x00000000)		// 判断连接是否断开
		{
			return false;
		}

		m_pConn->RollbackTrans();
	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("事务回滚失败！"));

		return false;
	}

	return true;
}

bool CADOOperate::ExecuteSql( CString strSql )
{
// 	if(s_pConm == NULL)
// 	{
// 		::CoInitialize(NULL);
// 		if(SUCCEEDED(s_pConm.CreateInstance(_T("ADODB.Connection")))) 
// 		{
// 			//if(s_pConm->Open("Driver=SQLite3 ODBC Driver;Database=jo_db_local.db",_T(""),_T(""),adModeUnknown)) //打开数据库
// 			if(s_pConm->Open("Driver=SQLite3 ODBC Driver;Database=jo_db_local.db",_T(""),_T(""),adModeShareDenyNone)) //打开数据库
// 			{
// 			}
// 		}
// 	}
// 	try
// 	{
// 		s_pConm->Execute((_bstr_t)strSql,&vtMissing, adCmdText);
// 		//s_pConm->Execute((_bstr_t)strSql,&vtMissing, adAsyncExecute);
// 	}
// 	catch(_com_error e)
// 	{
// 		return false;
// 	}

	return true;
}

bool CADOOperate::ReleaseCom()
{
	CoUninitialize();	// 卸载COM库	

	return true;
}

bool CADOOperate::InitTransConnection( _ConnectionPtr &pConn,const string &dbString /*= ""*/ )
{
	HRESULT hr;
	try
	{
		if(dbString.empty())
		{
			if(s_pConn == NULL)
			{
				hr = CoInitialize(0);
				if(SUCCEEDED(hr))  
				{
					//hr = s_pConn.CreateInstance(_uuidof(Connection)); 
					hr = s_pConn.CreateInstance("ADODB.Connection");///创建Connection对象   
					if(SUCCEEDED(hr))    
					{                
						s_pConn->PutIsolationLevel(adXactSerializable); //隔离事务的执行 

						hr = s_pConn->Open("Driver=SQLite3 ODBC Driver;Database=jo_db_local.db","","",-1); 					
					}
				}	
			}
			else
			{
				pConn = s_pConn;

				return true;
			}
		}
		else
		{
			if(s_pConn != NULL)
				s_pConn->Close();
			hr = CoInitialize(0);

			if(SUCCEEDED(hr))  
			{
				//hr = s_pConn.CreateInstance(_uuidof(Connection)); 
				hr = s_pConn.CreateInstance("ADODB.Connection");///创建Connection对象   
				if(SUCCEEDED(hr))    
				{                
					s_pConn->PutIsolationLevel(adXactSerializable); //隔离事务的执行 

					hr = s_pConn->Open(_bstr_t(dbString.c_str()),"","",-1); 			
				}
			}
		}
		pConn = s_pConn;
	}
	catch (_com_error e)
	{
		return false;
	}
	return SUCCEEDED(hr);
}

bool CADOOperate::InitTransRecordset(_RecordsetPtr &pRecord)
{
	HRESULT hr;

	try
	{
		//hr = pRecord.CreateInstance(_uuidof(Recordset)); 
		hr = pRecord.CreateInstance("ADODB.Recordset");   
		if(SUCCEEDED(hr))
		{
			pRecord->put_CursorLocation(adUseClient);   //使用客户端游标，客户端无法察觉服务器数据更新 adUseServer adUseClient
		}
	}
	catch(_com_error e)
	{
		return false;
	}
	return SUCCEEDED(hr);
}

bool CADOOperate::OpenTransRecordset( _ConnectionPtr &pConn,_RecordsetPtr &pRecord,const string &sqlString )
{
	HRESULT hr;

	try
	{
		if(pConn != NULL && pRecord != NULL)
		{
			pRecord->Open(_variant_t(sqlString.c_str()),_variant_t((IDispatch*)pConn,true),adOpenDynamic,adLockOptimistic ,adCmdText);  

			hr = pRecord->Requery(adOptionUnspecified);

			if(!pRecord->adoEOF)
				pRecord->MoveFirst();
		}
	}
	catch(_com_error e)
	{
		return false;
	}
	return SUCCEEDED(hr);
}
