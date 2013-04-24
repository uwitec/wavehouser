// CDialog_Material_Stats.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Material_Stats.h"
#include "CControl_material.h"

// CDialog_Material_Stats �Ի���

IMPLEMENT_DYNAMIC(CDialog_Material_Stats, CDialog)

CDialog_Material_Stats::CDialog_Material_Stats(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Material_Stats::IDD, pParent)
{

}

CDialog_Material_Stats::~CDialog_Material_Stats()
{
}

void CDialog_Material_Stats::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_modal);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_tBegin_ctrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_tEnd_ctrl);
	DDX_Control(pDX, IDC_STATIC_S, m_pieChart_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_Material_Stats, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_Material_Stats::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_CHECK2, &CDialog_Material_Stats::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CDialog_Material_Stats ��Ϣ�������

BOOL CDialog_Material_Stats::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_modal.AddString(_T("��������"));
	m_modal.AddString(_T("��������"));
	m_modal.AddString(_T("���ϼ۸�"));

	m_modal.SetCurSel(0);
	//CRect dlgRect;
	//m_pieChart_ctrl.GetClientRect(dlgRect);
	//
	//int tmp = dlgRect.Width() - dlgRect.Height();
	//if(tmp != 0)
	//{
	//	dlgRect.bottom += tmp;
	//	//dlgRect.right += tmp;
	//	m_pieChart_ctrl.SetWindowPos(&wndTop,dlgRect.top,dlgRect.left,dlgRect.bottom,dlgRect.right,SWP_NOMOVE);
	//}

	//m_pieChart_ctrl.SetEPos(CRect(50,50,300,300));
	m_pieChart_ctrl.SetEPos();
	//ShowEllipse();
	OnBnClickedSearchBtn();

	return TRUE;
}

void CDialog_Material_Stats::OnBnClickedSearchBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if(BST_CHECKED == IsDlgButtonChecked( IDC_CHECK2 ))
	{
		m_tBegin_ctrl.GetWindowText(m_searcher.m_tBegin);
		m_tEnd_ctrl.GetWindowText(m_searcher.m_tEnd);
		if(m_searcher.m_tBegin.IsEmpty() || m_searcher.m_tEnd.IsEmpty())
		{
			CRuntimeMessageBox::RunMessageBox("��������ȷ��ʱ��");
			return;
		}
	}
	else
	{
		m_searcher.m_aBegin.Empty();
		m_searcher.m_tEnd.Empty();
	}
	CControl_material tmp;
	m_searchDates = tmp.SearchList_Material(m_searcher);

	FormatSearchDates(m_modal.GetCurSel());
}

void CDialog_Material_Stats::FormatSearchDates( const int &modal /*= 0*/ )
{
	vector<PieData > datas;
	for (int i=0 ; i<m_searchDates.size();i++)
	{
		PieData tmp;
		tmp.PieNum = 1;
		if( (modal == 0 && !m_searchDates[i].m_name.IsEmpty()) ||//����
			(modal == 1 && !m_searchDates[i].m_manufacturer.IsEmpty()) ||
			(modal == 2 && !m_searchDates[i].m_price.IsEmpty()))
		{
			for (int j = 0;j < m_searchDates.size() ; j++)
			{
				if (i == j)
					continue;
				if(modal == 0 && m_searchDates[i].m_name == m_searchDates[j].m_name && !m_searchDates[j].m_name.IsEmpty()) //����
				{
					tmp.PieName = m_searchDates[j].m_name;
					m_searchDates[j].m_name.Empty();
					tmp.PieNum ++;					
				}
				else if(modal == 1 && m_searchDates[i].m_manufacturer == m_searchDates[j].m_manufacturer && !m_searchDates[j].m_manufacturer.IsEmpty())
				{
					tmp.PieName = m_searchDates[j].m_manufacturer;
					m_searchDates[j].m_manufacturer.Empty();
					tmp.PieNum ++;	
				}
				else if (modal == 2 && m_searchDates[i].m_price == m_searchDates[j].m_price && !m_searchDates[j].m_price.IsEmpty())
				{
					tmp.PieName = m_searchDates[j].m_price;
					m_searchDates[j].m_price.Empty();
					tmp.PieNum ++;	
				}
			}
			if(tmp.PieName.IsEmpty())
				tmp.PieName = modal == 0  ? m_searchDates[i].m_name : modal == 1 ?m_searchDates[i].m_manufacturer:m_searchDates[i].m_price;
			if (!tmp.PieName.IsEmpty() )
			{
				tmp.PieNum = tmp.PieNum == 1 ? 1 : tmp.PieNum; 

				datas.push_back(tmp);
			}
		}
	}	
	m_pieChart_ctrl.FormatStaticDatas(datas);
}

void CDialog_Material_Stats::ShowEllipse()
{
	vector<PieData > datas;
	float NUM = 0.0000;
	for (int i=0;i< 21;i++)
	{
		PieData tmp;
		tmp.PieName.Format(_T("ģ��%d"),i + 1);
		tmp.PieNum = i*30 + i*i + 10;

		NUM += tmp.PieNum;
		datas.push_back(tmp);
	}

	m_pieChart_ctrl.FormatStaticDatas(datas);
}
void CDialog_Material_Stats::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_tBegin_ctrl.EnableWindow(BST_CHECKED == IsDlgButtonChecked( IDC_CHECK2 ));
	m_tEnd_ctrl.EnableWindow(BST_CHECKED == IsDlgButtonChecked( IDC_CHECK2 ));
}
