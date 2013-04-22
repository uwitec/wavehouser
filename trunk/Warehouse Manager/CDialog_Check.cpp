// CDialog_Check.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Check.h"
//#include "afxdialogex.h"
#include "CDialog_Material.h"
#include "CDialog_UserInfo.h"
#include "CDialog_Class.h"
#include "CControl_check.h"
#include "CControl_user.h"
#include "CControl_class.h"
#include "CControl_material.h"

// CDialog_Check 对话框

IMPLEMENT_DYNAMIC(CDialog_Check, CDialog)

CDialog_Check::CDialog_Check(BOOL checkModal /*= TRUE*/,CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Check::IDD, pParent)
{
	m_checkModal =  checkModal;
}

CDialog_Check::~CDialog_Check()
{
}

void CDialog_Check::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_mName_ctrl);
	DDX_Control(pDX, IDC_EDIT5, m_mNum_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_total_ctrl);
	DDX_Control(pDX, IDC_EDIT8, m_wName_ctrl);
	DDX_Control(pDX, IDC_COMBO2, m_cName_ctrl);
	DDX_Control(pDX, IDC_COMBO3, m_pName_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_telPhone_ctrl);
	DDX_Control(pDX, IDC_EDIT7, m_detail_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_Check, CDialog)
	//ON_WM_INITDIALOG()
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_Check::OnBnClickedAddMaterialBtn)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog_Check::OnBnClickedAddClassBtn)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialog_Check::OnBnClickedAddPeopleBtn)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_Check::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_Check::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_Check 消息处理程序

BOOL CDialog_Check::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(m_checkModal)
	{
		SetWindowText(_T("购进"));
	}
	else
	{
		SetWindowText(_T("支出"));
	}

	InitComobox();

	if(!m_date.GetId().empty())
	{
		m_date.m_material = m_allMaterial.at(m_mName_ctrl.GetCurSel());
		int index = 0;
		for (index = 0; index < m_allMaterial.size();index ++)
			if (m_allMaterial[index].GetId() == m_date.GetId())
				break;
		m_mName_ctrl.SetCurSel(index);
		char cTmp[20] ={0};
		itoa(m_date.m_num,cTmp,10);
		m_mNum_ctrl.SetWindowText(m_dateChange.stringToCstring(string(cTmp)));
		memset(cTmp,0,20);
		ltoa(m_date.m_total,cTmp,10);
		m_total_ctrl.SetWindowText(m_dateChange.stringToCstring(string(cTmp)));
		for(index = 0;index<m_allClass.size();index ++)
			if(m_allClass[index].GetId() == m_date.m_class.GetId())
				break;
		m_cName_ctrl.SetCurSel(index);
		m_wName_ctrl.SetWindowText(m_date.m_operateWare);
		for (index = 0;index <m_allUser.size();index ++)
			if (m_allUser[index].GetId() == m_date.m_userInfo.GetId())
				break;
		m_pName_ctrl.SetCurSel(index);
		m_telPhone_ctrl.SetWindowText(m_date.m_tellPhone);
		m_detail_ctrl.SetWindowText(m_date.m_detail);
	}

	return TRUE;
}

void CDialog_Check::InitComobox(const int &initFlag )
{
	CDate_search condition;
	if(initFlag == -1 || initFlag == 0)
	{
		CControl_material tmpm;
		m_allMaterial = tmpm.SearchList_Material(condition);

		m_mName_ctrl.Clear();
		for (int i = 0;i< m_allMaterial.size() ;i++)
		{
			m_mName_ctrl.AddString(m_allMaterial[i].m_name);
		}
		m_mName_ctrl.SetCurSel(0);
	}
	if(initFlag == -1 || initFlag == 1)
	{
		CControl_user tmpu;
		m_allUser = tmpu.SearchList_UserInfo(condition);
		m_pName_ctrl.Clear();
		for (int i = 0;i< m_allUser.size() ;i++)
		{
			m_pName_ctrl.AddString(m_allUser[i].m_name);
		}
		m_pName_ctrl.SetCurSel(0);
	}
	if (initFlag == -1 || initFlag == 2)
	{
		CControl_class tmpc;
		m_allClass = tmpc.SearchList_Class(condition);
		m_cName_ctrl.Clear();
		for (int i = 0;i< m_allClass.size() ;i++)
		{
			m_cName_ctrl.AddString(m_allClass[i].m_name);
		}
		m_cName_ctrl.SetCurSel(0);
	}
}

void CDialog_Check::OnBnClickedAddMaterialBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_Material dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_allMaterial.push_back(dlg.GetDate());
	
		m_mName_ctrl.AddString(dlg.GetDate().m_name);

		m_mName_ctrl.SetCurSel(m_allMaterial.size() - 1);
	}
}


void CDialog_Check::OnBnClickedAddClassBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_CLass dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_allClass.push_back(dlg.GetDate());

		m_cName_ctrl.AddString(dlg.GetDate().m_name);

		m_cName_ctrl.SetCurSel(m_allClass.size() - 1);
	}
}


void CDialog_Check::OnBnClickedAddPeopleBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_UserInfo dlg(false);
	if(dlg.DoModal() == IDOK)
	{
		m_allUser.push_back(dlg.GetDate());

		m_pName_ctrl.AddString(dlg.GetDate().m_name);

		m_pName_ctrl.SetCurSel(m_allUser.size() - 1);
	}
}


void CDialog_Check::OnBnClickedBtbSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_date.m_material = m_allMaterial.at(m_mName_ctrl.GetCurSel());
	if(m_date.m_material.GetId().empty())
	{
		CRuntimeMessageBox::RunMessageBox("请选择正确的材料");

		return;
	}
	CString tmp;
	m_mNum_ctrl.GetWindowText(tmp);
	if(tmp.IsEmpty() || tmp.SpanIncluding(_T("1234567890")) != tmp)
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的数目！");

		return;
	}
	else
	{
		m_date.m_num = atoi((const char *)tmp.GetBuffer(tmp.GetLength()));
		double price = atof(m_dateChange.CStringtostring(m_date.m_material.m_price).c_str());
		tmp.Format(_T("%.2lf"),m_date.m_num * price);
		m_total_ctrl.SetWindowText(tmp);
		m_date.m_total = price;
	}
	m_wName_ctrl.GetWindowText(m_date.m_operateWare);
	if(m_date.m_operateWare.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的仓库");

		return;
	}

	m_date.m_class = m_allClass.at(m_cName_ctrl.GetCurSel());
	if(m_date.m_class.GetId().empty())
	{
		CRuntimeMessageBox::RunMessageBox("请选择正确的部门名称");

		return;
	}
	m_date.m_userInfo = m_allUser.at(m_pName_ctrl.GetCurSel());
	if(m_date.m_userInfo.GetId().empty())
	{
		if(m_checkModal)
			CRuntimeMessageBox::RunMessageBox("请输入正确的购进人员");
		else
			CRuntimeMessageBox::RunMessageBox("请输入正确的支出人员");

		return;
	}
	m_telPhone_ctrl.GetWindowText(m_date.m_tellPhone);
	if(m_date.m_tellPhone.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("请输入正确的电话号码");

		return;
	}
	m_detail_ctrl.GetWindowText(m_date.m_detail);

	m_date.m_checkModal = m_checkModal;

	CControl_check tmpc;

	tmpc.SetData(&m_date);
	if (tmpc.Save())
	{
		CRuntimeMessageBox::RunMessageBox("保存成功！");

		OnOK();
	}
	else
	{
		CRuntimeMessageBox::RunMessageBox("保存失败！");
	}
}


void CDialog_Check::OnBnClickedBtbQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
