// CDialog_Material.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Material.h"
#include "CControl_material.h"
#include "CDialog_Material_List.h"
// CDialog_Material �Ի���

IMPLEMENT_DYNAMIC(CDialog_Material, CDialog)

CDialog_Material::CDialog_Material(const bool &isEdit/* = false*/,CWnd* pParent /*=NULL*/)
: CDialog(CDialog_Material::IDD, pParent)
{
	m_isEdit = isEdit;
}

CDialog_Material::~CDialog_Material()
{
}

void CDialog_Material::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name_ctrl);
	DDX_Control(pDX, IDC_EDIT2, m_modal_ctrl);
	DDX_Control(pDX, IDC_EDIT3, m_manufacturer_ctrl);
	DDX_Control(pDX, IDC_EDIT6, m_unit_ctrl);
	DDX_Control(pDX, IDC_EDIT4, m_price_ctrl);
	DDX_Control(pDX, IDC_EDIT7, m_detail_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_Material, CDialog)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_Material::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_Material::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_Material ��Ϣ�������

BOOL CDialog_Material::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(!m_date.GetId().empty())
	{
		if(m_date.m_unit.IsEmpty())
		{
			CControl_material tmp;
			m_date = tmp.Search_byId(m_date.GetId());
		}
		m_name_ctrl.SetWindowText(m_date.m_name);
		m_modal_ctrl.SetWindowText(m_date.m_modal);
		m_manufacturer_ctrl.SetWindowText(m_date.m_manufacturer);
		m_unit_ctrl.SetWindowText(m_date.m_unit);
		m_price_ctrl.SetWindowText(m_date.m_price);
		m_detail_ctrl.SetWindowText(m_date.m_detail);
	}
	return FALSE;
}

void CDialog_Material::OnBnClickedBtbSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_date.GetDel())
		if(::MessageBox(::GetActiveWindow(),_T("����Ϣ�Ѿ���ɾ���ˣ��Ƿ����±���ָ���"),_T("��ʾ"),MB_YESNO) == IDNO)
			return ;
	m_name_ctrl.GetWindowText(m_date.m_name);
	if(m_date.m_name.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĳ�������");
		return;
	}
	m_modal_ctrl.GetWindowText(m_date.m_modal);
	if(m_date.m_modal.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�Ĳ����ͺ�");
		return;
	}
	m_manufacturer_ctrl.GetWindowText(m_date.m_manufacturer);
	if(m_date.m_manufacturer.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ����������");
		return;
	}
	m_unit_ctrl.GetWindowText(m_date.m_unit);
	if(m_date.m_unit.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�ĵ�λ");
		return;
	}
	m_price_ctrl.GetWindowText(m_date.m_price);
	if(m_date.m_price.IsEmpty())
	{
		CRuntimeMessageBox::RunMessageBox("��������ȷ�ĵ���");
		return;
	}
	m_detail_ctrl.GetWindowText(m_date.m_detail);

	CControl_material tmp;
	tmp.SetData(&m_date);
	if (tmp.Save())
	{
		CRuntimeMessageBox::RunMessageBox("����ɹ���");

		OnOK();
	}
	else
	{
		CRuntimeMessageBox::RunMessageBox("����ʧ�ܣ�");
	}
}


void CDialog_Material::OnBnClickedBtbQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}

void CDialog_Material::SetDate( const CDate_Material &date )
{
	m_date = date;
}

CDate_Material CDialog_Material::GetDate()
{
	return m_date;
}
