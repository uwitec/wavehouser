#include "StdAfx.h"
#include "CControl_DB.h"

CControl_DB::CControl_DB(void)
{
	m_pConn = NULL;
	m_pRst  = NULL;
}

CControl_DB::~CControl_DB(void)
{
	CoUninitialize();     // ж��COM��
}

bool CControl_DB::InitDB()
{
// 	CoInitialize(NULL);	                             //��ʼ��Com���
// 	_ConnectionPtr conPtr;	                         //���ݿ�����ָ��
// 
// 	conPtr.CreateInstance(__uuidof(Connection));	 //Connection���������ݿ��������������һ�ַ�ʽ
// 	// MySQL ODBC 5.1 DriverΪ�������ƣ�ȡ��������ΪMySql��װ����������localhostΪ��������ַ��testΪ���ݿ�����rootΪ�û�����MySqlĬ���û���Ϊroot����saΪ����
// 	CString conStr=_T("Driver={ MySQL ODBC 5.1 Driver };Server= localhost;Database=test;");
// 	/******************�������ݿ�********************/
// 	try
// 	{
// 		conPtr->ConnectionTimeout = 50;	 //��������ʱ��
// 		conPtr->Open((_bstr_t)conStr, "root","haipe", adModeUnknown);
// 	}
// 	catch(_com_error e)	 //��׽�쳣
// 	{
// 		AfxMessageBox(e.ErrorMessage());
// 	} 
// 	CoUninitialize();	 //�ͷ�com���

	return false;
}

//*********************************************
//ADO����������ݿ�
//*********************************************
bool CControl_DB::InitADOConn()
{	
	bool result = false;
	try
	{
		::CoInitialize(NULL);
		HRESULT flag = m_pConn.CreateInstance(_T("ADODB.Connection"));  //�������Ӷ���ʵ��
		if(SUCCEEDED(flag)) 
		{
			_bstr_t strConnect="Driver={ MySQL ODBC 5.1 Driver };Server= localhost;Database=warehouse_db;";

			result = SUCCEEDED(m_pConn->Open(strConnect, "root","haipe", adModeUnknown)); //�����ݿ�
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description()); //����������

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
//ADO�����ȡ��¼��
//*********************************************
_RecordsetPtr&  CControl_DB::OpenRecordset(string strSQL)
{
	try
	{
		if(m_pConn==0x00000000)	                        // �ж������Ƿ�Ͽ�
		{
			m_pConn=NULL;
			if(InitADOConn())	                        // ��������
			{

			}
		}
		m_pRst.CreateInstance("ADODB.Recordset");		//������¼������ʵ��
		m_pRst->raw_Close();                            // �رռ�¼��
		m_pRst->Open((_bstr_t)strSQL.c_str(),m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(e.Description());
	}

	return m_pRst;	// ���ؼ�¼��
}

//*********************************************
//�رռ�¼��
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
//�ر���ADO��������ӣ��ر����ݿ�����
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
//ִ����ɾ��sql���
//*********************************************
bool CControl_DB::ExecuteSQL(string strSQL)
{	
	try
	{
		if(m_pConn==0x00000000)		// �ж������Ƿ�Ͽ�
		{
			m_pConn=NULL;
			InitADOConn();		// ��������
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
//��ȡ�ܼ�¼����
//*******************************************

LONG64 CControl_DB::GetRecordsCount(string strSQL)
{
	LONG64 count;
	try
	{
		if(m_pConn==0X00000000)		// �ж������Ƿ�Ͽ�
			InitADOConn();		// ��������

		m_pRst.CreateInstance(_T("ADODB.Recordset"));//__uuidof(Recordset));		//������¼������ʵ��
		m_pRst->raw_Close();	// �رռ�¼��
		m_pRst->Open((_bstr_t)strSQL.c_str(),m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		//AfxMessageBox(e.Description());
		count = 0;
	}

	count =atoi((char*)(_bstr_t)m_pRst->GetCollect("count")) ;

	return count;	// ���ؼ�¼����
}

/************************************************************************/
/* ��ȡÿ���ֶε�ֵ����������                                                                     */
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

