#include "stdafx.h"
#include "CControl_DB.h"
#include "CStringTransform.h"

CADOOperate *CADOOperate::s_pADOOperate = NULL;
CADOOperate::CADOOperate()
{
	m_pConn = NULL;
	m_pConm = NULL;
}

CADOOperate::~CADOOperate()
{
	CoUninitialize();	// ж��COM��
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
		HRESULT hr = m_pConn.CreateInstance(__uuidof(Connection));  //�������Ӷ���ʵ��
		if(SUCCEEDED(hr)) 
		{
			//_bstr_t strConnect="Driver=MySQL ODBC 5.1 Driver;SERVER=127.0.0.1;UID=root;PWD=haipe;DATABASE=warehouse_db;PORT=3306";
			//_bstr_t strConnect="Driver=MySQL ODBC 5.1 Driver;SERVER=127.0.0.1;UID=root;PWD=haipe;DATABASE=warehouse_db;PORT=3306;CHARSET=GB2312";
			_bstr_t strConnect="Driver=SQLite3 ODBC Driver;Database=local.db";

			 hr = m_pConn->Open(strConnect,_T(""),_T(""),adModeUnknown); //�����ݿ�

			if(m_pConm == NULL)
				m_pConm.CreateInstance(_T("ADODB.Command"));
		}
		else
		{
			CRuntimeMessageBox::RunMessageBox(("�����������ݿ����ʵ��ʧ��!"));
		}
	}
	catch(_com_error e)
	{
		CRuntimeMessageBox::RunMessageBox(("���ݿ�����ʧ��!"));
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
		if(s_pADOOperate->m_pConn==0x00000000)		// �ж������Ƿ�Ͽ�
		{
			s_pADOOperate->m_pConn=NULL;
			s_pADOOperate->InitADOConn();		// ��������
		}
		recordset.CreateInstance("ADODB.Recordset");		//������¼������ʵ��
		recordset->put_CursorLocation(adUseClient);   
		recordset->Open((_bstr_t)strSQL.c_str(),s_pADOOperate->m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);

	}
	catch(_com_error e)
	{
		CRuntimeMessageBox::RunMessageBox(("��¼����ʧ�ܣ�"));

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
		if(s_pADOOperate->m_pConn==0x00000000)		// �ж������Ƿ�Ͽ�
		{
			s_pADOOperate->m_pConn=NULL;
			s_pADOOperate->InitADOConn();		// ��������
		}

		//m_pConn->Execute((_bstr_t)strSQL,&vtMissing,0);
		//m_pRst.CreateInstance(__uuidof(Recordset));		//������¼������ʵ��
		//m_pRst->raw_Close();	// �رռ�¼��
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

	return true;	// ���ؼ�¼��
}

LONG64 CADOOperate::GetRecordsCount( _RecordsetPtr &recordset,string strSQL )
{
	LONG64 count = 0;
	try
	{
		if(s_pADOOperate->m_pConn==0X00000000)		// �ж������Ƿ�Ͽ�
			s_pADOOperate->InitADOConn();		// ��������

		recordset.CreateInstance(_T("ADODB.Recordset"));//__uuidof(Recordset));		//������¼������ʵ��
		recordset->Open((_bstr_t)strSQL.c_str(),s_pADOOperate->m_pConn.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)
	{
		count = 0;
	}

	if (!recordset->adoEOF)
	{
		count =atoi((char*)(_bstr_t)recordset->GetCollect("count")) ;
	}

	return count;	// ���ؼ�¼����
}

std::string CADOOperate::GetCollectData( _RecordsetPtr &recordset,string name )
{
	string val;

	//_variant_t var = recordset->GetCollect((_bstr_t)(char *)name.c_str());
	_variant_t var = recordset->Fields->GetItem(name.c_str())->Value;

	if(var.vt != VT_NULL)
		val = (string)_bstr_t(var);

	//CStringTransform tmp;
	//return tmp.Gb2312ToUnicode((char *)val.c_str());
	return val;
}