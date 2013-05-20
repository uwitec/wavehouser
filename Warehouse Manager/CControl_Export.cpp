#include "stdafx.h"
#include "CControl_Export.h"
#include <fstream>
#include "CStringTransform.h"
using namespace std;
CControl_Export::CControl_Export(void)
{
}

CControl_Export::~CControl_Export(void)
{
}

bool CControl_Export::ExportUser( const vector<CDate_User> &dates )
{
	CStringTransform dateChange;
	//显示文件打开对话框
	CFileDialog dlg(FALSE, _T("CSV"),_T("*.csv"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("CSV Files(*.csv)|*.csv")); 
	if ( dlg.DoModal()!=IDOK ) 
		return false;
	//获取文件的绝对路径
	CString sFileName=dlg.GetPathName();

	ofstream outfile;
	outfile.open(sFileName);
	if (outfile.is_open())
	{
		string title = "序号,姓名,公司,年龄,电话,Email,详细信息\r";
		outfile.write(title.c_str(),title.length());
		
		char cTmp[10];
		for (int i=0;i<dates.size();i++)
		{
			memset(cTmp,0,10);
			itoa(i,cTmp,10);
			string dateLine = cTmp;

			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_name);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_companyName);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_age);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_tellPhone);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_email);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_detail);
			dateLine += "\r";
			outfile.write(dateLine.c_str(),dateLine.length());
		}
		outfile.close();

		return true;
	}

	return false;
}

bool CControl_Export::ExportMaterial( const vector<CDate_Material> &dates )
{
	CStringTransform dateChange;
	//显示文件打开对话框
	CFileDialog dlg(FALSE, _T("CSV"),_T("*.csv"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("CSV Files(*.csv)|*.csv")); 
	if ( dlg.DoModal()!=IDOK ) 
		return false;
	//获取文件的绝对路径
	CString sFileName=dlg.GetPathName();

	ofstream outfile;
	outfile.open(sFileName);
	if (outfile.is_open())
	{
		string title = "序号,材料名称,型号,生产厂家,单位,价格,详细信息\r";
		outfile.write(title.c_str(),title.length());

		char cTmp[10];
		for (int i=0;i<dates.size();i++)
		{
			memset(cTmp,0,10);
			itoa(i,cTmp,10);
			string dateLine = cTmp;

			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_name);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_modal);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_manufacturer);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_unit);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_price);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_detail);
			dateLine += "\r";
			outfile.write(dateLine.c_str(),dateLine.length());
		}
		outfile.close();

		return true;
	}

	return false;
}

bool CControl_Export::ExportCheck( const vector<CDate_check> &dates )
{

	CStringTransform dateChange;
	//显示文件打开对话框
	CFileDialog dlg(FALSE, _T("CSV"),_T("*.csv"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("CSV Files(*.csv)|*.csv")); 
	if ( dlg.DoModal()!=IDOK ) 
		return false;
	//获取文件的绝对路径
	CString sFileName=dlg.GetPathName();

	ofstream outfile;
	outfile.open(sFileName);
	if (outfile.is_open())
	{
		int m_checkModal;

		string title = "序号,类型,材料名称,操作员,部门,数量,总额,日期,电话,详细信息\r";
		outfile.write(title.c_str(),title.length());

		char cTmp[10];
		for (int i=0;i<dates.size();i++)
		{
			memset(cTmp,0,10);
			itoa(i+1,cTmp,10);
			string dateLine = cTmp;

			if(dates[i].m_checkModal)
				dateLine += ",入库,";
			else
				dateLine += ",出库,";

			dateLine += dateChange.CStringtostring(dates[i].m_material.m_name);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_userInfo.m_name);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_class.m_name);
			dateLine += ",";
			CString tmp;
			tmp.Format(_T("%d"),dates[i].m_num);
			dateLine += dateChange.CStringtostring(tmp);
			dateLine += ",";
			tmp.Format(_T("%.2lf"),dates[i].m_total);
			dateLine += dateChange.CStringtostring(tmp);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_time);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_tellPhone);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_detail);
			dateLine += "\r";
			outfile.write(dateLine.c_str(),dateLine.length());
		}
		outfile.close();

		return true;
	}

	return false;
}

bool CControl_Export::ExportClass( const vector<CDate_Class > &dates )
{
	CStringTransform dateChange;
	//显示文件打开对话框
	CFileDialog dlg(FALSE, _T("CSV"),_T("*.csv"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,_T("CSV Files(*.csv)|*.csv")); 
	if ( dlg.DoModal()!=IDOK ) 
		return false;
	//获取文件的绝对路径
	CString sFileName=dlg.GetPathName();

	ofstream outfile;
	outfile.open(sFileName);
	if (outfile.is_open())
	{
		string title = "序号,部门名称,负责人,部门人数,联系人,联系电话,详细信息\r";
		outfile.write(title.c_str(),title.length());

		char cTmp[10];
		for (int i=0;i<dates.size();i++)
		{
			memset(cTmp,0,10);
			itoa(i,cTmp,10);
			string dateLine = cTmp;

			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_name);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_pName);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_num);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_contact);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_tellPhone);
			dateLine += ",";
			dateLine += dateChange.CStringtostring(dates[i].m_detail);
			dateLine += "\r";
			outfile.write(dateLine.c_str(),dateLine.length());
		}
		outfile.close();

		return true;
	}

	return false;
}
