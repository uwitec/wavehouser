#include "stdafx.h"
#include "ADOOperate.h"
#include "CRuntimeMessageBox.h"

CADOOperate *CADOOperate::s_pADOOperate = NULL;
CADOOperate::CADOOperate()
{
	m_pConn = NULL;
	m_pConm = NULL;
}

CADOOperate::~CADOOperate()
{
	CoUninitialize();	// 卸载COM库
}

CADOOperate * CADOOperate::InitADO()
{
	if(s_pADOOperate == NULL)
	{
		s_pADOOperate = new CADOOperate();
		s_pADOOperate->InitADOConn();
	}

	return s_pADOOperate;
}

bool CADOOperate::InitADOConn()
{		
	try
	{
		::CoInitialize(NULL);
		HRESULT hr = s_pADOOperate->m_pConn.CreateInstance(_T("ADODB.Connection"));  //创建连接对象实例
		if(SUCCEEDED(hr)) 
		{
			_bstr_t strConnect="Driver={ MySQL ODBC 5.1 Driver };Server= localhost;Database=warehouse_db;";

			m_pConn->Open(strConnect,_T("root"),_T("haipe"),adModeUnknown); //打开数据库

			if(m_pConm == NULL)
				m_pConm.CreateInstance(_T("ADODB.Command"));
		}
		else
		{
			CRuntimeMessageBox::RunMessageBox(("创建连接数据库对象实例失败!"));
		}
	}
	catch(_com_error e)
	{
		CRuntimeMessageBox::RunMessageBox(("数据库连接失败!"));
		return false;
	}
	catch (...)
	{
		//AfxMessageBox(L"SYS Error");
		return false;
	}

	return true;
}

bool CADOOperate::OpenRecordset( _RecordsetPtr &recordset,string strSQL )
{
	try
	{
		if(s_pADOOperate->m_pConn==0x00000000)		// 判断连接是否断开
		{
			s_pADOOperate->m_pConn=NULL;
			s_pADOOperate->InitADOConn();		// 重新连接
		}
		recordset.CreateInstance("ADODB.Recordset");		//创建记录集对象实例
		recordset->Open((_bstr_t)strSQL.c_str(),s_pADOOperate->m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

	}
	catch(_com_error e)
	{
		CRuntimeMessageBox::RunMessageBox(("记录集打开失败！"));

		return false;
	}

	return true;
}

void CADOOperate::CloseADOConn()
{	
	if (s_pADOOperate->m_pConn != NULL)
	{
		if (s_pADOOperate->m_pConn->State)
		{
			s_pADOOperate->m_pConn->Close();
		}
	}
	s_pADOOperate->m_pConn = NULL;	
}

bool CADOOperate::ExecuteSQL(string strSQL)
{	
	try
	{
		if(s_pADOOperate->m_pConn==0x00000000)		// 判断连接是否断开
		{
			s_pADOOperate->m_pConn=NULL;
			s_pADOOperate->InitADOConn();		// 重新连接
		}

		//m_pConn->Execute((_bstr_t)strSQL,&vtMissing,0);
		//m_pRst.CreateInstance(__uuidof(Recordset));		//创建记录集对象实例
		//m_pRst->raw_Close();	// 关闭记录集
		//m_pRst->Open((_bstr_t)strSQL,m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		s_pADOOperate->m_pConm->ActiveConnection = s_pADOOperate->m_pConn;
		s_pADOOperate->m_pConm->CommandType = adCmdText;
		s_pADOOperate->m_pConm->CommandText = _bstr_t(strSQL.c_str());

		_variant_t vNull;
		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;

		s_pADOOperate->m_pConm->Execute(&vNull, &vNull, adCmdText);
	}
	catch(_com_error e)
	{
		//AfxMessageBox(e.Description());
		return false;
	}

	return true;	// 返回记录集
}

LONG64 CADOOperate::GetRecordsCount( _RecordsetPtr &recordset,string strSQL )
{
	LONG64 count;
	try
	{
		if(s_pADOOperate->m_pConn==0X00000000)		// 判断连接是否断开
			s_pADOOperate->InitADOConn();		// 重新连接

		recordset.CreateInstance(_T("ADODB.Recordset"));//__uuidof(Recordset));		//创建记录集对象实例
		recordset->Open((_bstr_t)strSQL.c_str(),s_pADOOperate->m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		count = 0;
	}

	count =atoi((char*)(_bstr_t)recordset->GetCollect("count")) ;

	return count;	// 返回记录总数
}

std::string CADOOperate::GetCollectData( _RecordsetPtr &recordset,string name )
{
	string val;

	_variant_t var = recordset->GetCollect((_bstr_t)(char *)name.c_str());

	if(var.vt != VT_NULL)
		val = (string)_bstr_t(var);

	return val;
}
