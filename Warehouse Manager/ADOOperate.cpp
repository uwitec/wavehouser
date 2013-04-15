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
	CoUninitialize();	// ж��COM��
}

//*********************************************
//ADO����������ݿ�
//jiashixiong  
//*********************************************
bool CADOOperate::InitADOConn()
{	
	
	try
	{
		::CoInitialize(NULL);
		HRESULT hr=m_pConn.CreateInstance(_T("ADODB.Connection"));  //�������Ӷ���ʵ��
		if(SUCCEEDED(hr)) 
		{
			//_bstr_t strConnect="DRIVER={SQLite3 ODBC Driver};\uid=;pwd=;DBQ=jo_db_local.db;";
			_bstr_t strConnect="Driver=SQLite3 ODBC Driver;Database=jo_db_local.db";
			//m_pConn->ConnectionString=strConnect;
			m_pConn->Open(strConnect,_T(""),_T(""),adModeUnknown); //�����ݿ�

			if(m_pConm == NULL)
				m_pConm.CreateInstance(_T("ADODB.Command"));
				//m_pConm.CreateInstance(__uuidof(Command));
		}
		else
		{
			CMyBox::Show(_T("�����������ݿ����ʵ��ʧ��!"));
		}

	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("���ݿ�����ʧ��!"));
		//AfxMessageBox(e.Description()); //����������
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
//ADO�����ȡ��¼��
//jiashixiong  
//*********************************************
_RecordsetPtr&  CADOOperate::OpenRecordset(CString strSQL)
{
	//ASSERT(!strSQL.IsEmpty());										//SQL��䲻��Ϊ��

	try
	{
		if(m_pConn==0x00000000)		// �ж������Ƿ�Ͽ�
		{
			m_pConn=NULL;
			InitADOConn();		// ��������
		}
		m_pRst.CreateInstance("ADODB.Recordset");		//������¼������ʵ��
		m_pRst->raw_Close();	// �رռ�¼��
		m_pRst->Open((_bstr_t)strSQL,m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		
	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("��¼����ʧ�ܣ�"));
		//AfxMessageBox(e.Description());

	}

	return m_pRst;	// ���ؼ�¼��
}

_RecordsetPtr& CADOOperate::GetRecordsetPtr(CString strSQL)
{
	try
	{
		if(m_pConn==0x00000000)		// �ж������Ƿ�Ͽ�
		{
			m_pConn=NULL;
			InitADOConn();		// ��������
		}

		if(!strSQL.IsEmpty())
		{
			m_pRst.CreateInstance("ADODB.Recordset");		//������¼������ʵ��
			m_pRst->raw_Close();	// �رռ�¼��
			m_pRst->Open((_bstr_t)strSQL,m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
		}
	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("��¼����ʧ�ܣ�"));
		//AfxMessageBox(e.Description());

	}

	return m_pRst;
}
//*********************************************
//�رռ�¼��
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
//�ر���ADO��������ӣ��ر����ݿ�����
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
	//	����˵��������ָ��_RecordsetPtr��_ConnectionPtr�ڳ����������ǻ��Զ��ͷŵģ�
	//  Ҳ����˵ָ����CreateInstance()��ʱ������ڴ棬�����������ͷţ�
	//  �����Լ�����Release()�����Ǳ���ģ����������п��ܳ�������ΪNULL����ȫ���Բ��õġ� 
	//	m_pConn->Release();
	
}
//*********************************************
//ִ����ɾ��sql���
//jiashixiong
//*********************************************
bool CADOOperate::ExecuteSQL(CString strSQL)
{	
	try
	{
		if(m_pConn==0x00000000)		// �ж������Ƿ�Ͽ�
		{
			m_pConn=NULL;
			InitADOConn();		// ��������
		}

		//m_pConn->Execute((_bstr_t)strSQL,&vtMissing,0);
		//m_pRst.CreateInstance(__uuidof(Recordset));		//������¼������ʵ��
		//m_pRst->raw_Close();	// �رռ�¼��
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

	return true;	// ���ؼ�¼��
}

//*******************************************
//��ȡ�ܼ�¼����
//*******************************************

LONG64 CADOOperate::GetRecordsCount(CString strSQL)
{
	LONG64 count;
	try
	{
		if(m_pConn==0X00000000)		// �ж������Ƿ�Ͽ�
			InitADOConn();		// ��������

		m_pRst.CreateInstance(_T("ADODB.Recordset"));//__uuidof(Recordset));		//������¼������ʵ��
		m_pRst->raw_Close();	// �رռ�¼��
		m_pRst->Open((_bstr_t)strSQL,m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		//AfxMessageBox(e.Description());
		count = 0;
	}

	//ֻȡ��һ����¼
	//while(!m_pRst->adoEOF)
	//{
	count =atoi((char*)(_bstr_t)m_pRst->GetCollect("count")) ;
	//	m_pRst->MoveNext();//����¼��ָ���ƶ�����һ����¼
	//}

	return count;	// ���ؼ�¼����
}

/************************************************************************/
/* ��ȡÿ���ֶε�ֵ����������                                                                     */
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

	_variant_t vars = "�������Ĺ�������,��Ҫ����.NET\JAVA��WEB����,�Ա���ҵ���ƶ�ҵ�񿪷���һ���Ĺ�������,����.NET����ܹ�����,Spring��MVC����,��Ϥʹ��jquery,��ˢ�¼���,����ʹ��ORACLE\SQL2000\SQL2005���ݿ�,��ͨ���ݿ�洢���̱�д,��������oracle���ݿ�߼����С�JOB��,�����ݿ���Ʒ�����һ���Ĺ������顣��Ϥ.NET\JAVA��AD��Exchange�Ĳ���,��ϤIIS�������ڽ�������Ŀ�����ж�������Ҫ��ɫ,�缼���ѵ�Ĺ��ơ�����ҵ��ģ��ı�д����Ա�����������ȵ�,�߱�һ����ͻ�������ͨ������ �ɾ������";

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
		if(m_pConn == 0x00000000)		// �ж������Ƿ�Ͽ�
		{
			return false;
		}

		m_pConn->BeginTrans();
	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("������ʧ�ܣ�"));

		return false;
	}

	return true;
}

bool CADOOperate::CommitTrans()
{
	try
	{
		if(m_pConn == 0x00000000)		// �ж������Ƿ�Ͽ�
		{
			return false;
		}

		m_pConn->CommitTrans();
	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("�����ύʧ�ܣ�"));

		return false;
	}

	return true;
}

bool CADOOperate::RollbackTrans()
{
	try
	{
		if(m_pConn == 0x00000000)		// �ж������Ƿ�Ͽ�
		{
			return false;
		}

		m_pConn->RollbackTrans();
	}
	catch(_com_error e)
	{
		CMyBox::Show(_T("����ع�ʧ�ܣ�"));

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
// 			//if(s_pConm->Open("Driver=SQLite3 ODBC Driver;Database=jo_db_local.db",_T(""),_T(""),adModeUnknown)) //�����ݿ�
// 			if(s_pConm->Open("Driver=SQLite3 ODBC Driver;Database=jo_db_local.db",_T(""),_T(""),adModeShareDenyNone)) //�����ݿ�
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
	CoUninitialize();	// ж��COM��	

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
					hr = s_pConn.CreateInstance("ADODB.Connection");///����Connection����   
					if(SUCCEEDED(hr))    
					{                
						s_pConn->PutIsolationLevel(adXactSerializable); //���������ִ�� 

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
				hr = s_pConn.CreateInstance("ADODB.Connection");///����Connection����   
				if(SUCCEEDED(hr))    
				{                
					s_pConn->PutIsolationLevel(adXactSerializable); //���������ִ�� 

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
			pRecord->put_CursorLocation(adUseClient);   //ʹ�ÿͻ����α꣬�ͻ����޷�������������ݸ��� adUseServer adUseClient
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
