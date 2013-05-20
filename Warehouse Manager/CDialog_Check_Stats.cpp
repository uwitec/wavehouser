// CDialog_Check_Stats.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Check_Stats.h"
#include "CControl_check.h"
//#include "afxdialogex.h"


// CDialog_Check_Stats 对话框

IMPLEMENT_DYNAMIC(CDialog_Check_Stats, CDialog)

CDialog_Check_Stats::CDialog_Check_Stats(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Check_Stats::IDD, pParent)
{

}

CDialog_Check_Stats::~CDialog_Check_Stats()
{
}

void CDialog_Check_Stats::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_tBegin_ctrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_tEnd_ctrl);
	DDX_Control(pDX, IDC_STATIC_S, m_pieChart_ctrl);
	DDX_Control(pDX, IDC_COMBO1, m_modal);
}


BEGIN_MESSAGE_MAP(CDialog_Check_Stats, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_Check_Stats::OnBnClickedSearchBtn)
	ON_BN_CLICKED(IDC_CHECK2, &CDialog_Check_Stats::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CDialog_Check_Stats 消息处理程序

BOOL CDialog_Check_Stats::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_modal.AddString(_T("类型"));
	m_modal.AddString(_T("材料"));
	m_modal.AddString(_T("部门"));
	m_modal.AddString(_T("人员"));
	m_modal.AddString(_T("日期"));
	m_modal.AddString(_T("金额"));

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
void CDialog_Check_Stats::OnBnClickedSearchBtn()
{

	if(BST_CHECKED == IsDlgButtonChecked( IDC_CHECK2 ))
	{
		m_tBegin_ctrl.GetWindowText(m_searcher.m_tBegin);
		m_tEnd_ctrl.GetWindowText(m_searcher.m_tEnd);
		if(m_searcher.m_tBegin.IsEmpty() || m_searcher.m_tEnd.IsEmpty())
		{
			CRuntimeMessageBox::RunMessageBox("请输入正确的时间");
			return;
		}
	}
	else
	{
		m_searcher.m_aBegin.Empty();
		m_searcher.m_tEnd.Empty();
	}
	CControl_check tmp;
	m_searchDates = tmp.SearchList_Check(m_searcher);

	FormatSearchDates(m_modal.GetCurSel());
}


void CDialog_Check_Stats::FormatSearchDates( const int &modal /*= 0*/ )
{
	vector<PieData > datas;
	for (int i=0 ; i<m_searchDates.size();i++)
	{
		PieData tmp;
		tmp.PieNum = 1;
		if( (modal == 0 /*&& !m_searchDates[i].m_checkModal*/ ) ||//名称
			(modal == 1 && !m_searchDates[i].m_material.m_name.IsEmpty()) ||
			(modal == 2 && !m_searchDates[i].m_class.m_name.IsEmpty()) ||
			(modal == 3 && !m_searchDates[i].m_userInfo.m_name.IsEmpty()) ||
			(modal == 4 && !m_searchDates[i].m_time.IsEmpty()) ||
			(modal == 5 ))
		{
			for (int j = 0;j < m_searchDates.size() ; j++)
			{
				if (i == j)
					continue;
				if(modal == 0 && m_searchDates[i].m_checkModal == m_searchDates[j].m_checkModal && m_searchDates[j].m_checkModal == -1) //名称
				{
					tmp.PieName = m_searchDates[j].m_checkModal == 1 ? _T("入库") :_T("出库");
					m_searchDates[j].m_checkModal = -1;
					tmp.PieNum ++;					
				}
				else if(modal == 1 && m_searchDates[i].m_material.m_name == m_searchDates[j].m_material.m_name && !m_searchDates[j].m_material.m_name.IsEmpty())
				{
					tmp.PieName = m_searchDates[j].m_material.m_name;
					m_searchDates[j].m_material.m_name.Empty();
					tmp.PieNum ++;	
				}
				else if (modal == 2 && m_searchDates[i].m_class.m_name == m_searchDates[j].m_class.m_name && !m_searchDates[j].m_class.m_name.IsEmpty())
				{
					tmp.PieName = m_searchDates[j].m_class.m_name;
					m_searchDates[j].m_class.m_name.Empty();
					tmp.PieNum ++;	
				}
				else if (modal == 3 && m_searchDates[i].m_userInfo.m_name == m_searchDates[j].m_userInfo.m_name && !m_searchDates[j].m_userInfo.m_name.IsEmpty())
				{
					tmp.PieName = m_searchDates[j].m_userInfo.m_name;
					m_searchDates[j].m_userInfo.m_name.Empty();
					tmp.PieNum ++;	
				}
				else if (modal == 4 && m_searchDates[i].m_time == m_searchDates[j].m_time && !m_searchDates[j].m_time.IsEmpty())
				{
					tmp.PieName = m_searchDates[j].m_time;
					m_searchDates[j].m_time.Empty();
					tmp.PieNum ++;	
				}
				else if (modal == 5 && m_searchDates[i].m_total == m_searchDates[j].m_total && !m_searchDates[j].m_total != -1)
				{
					tmp.PieName.Format(_T("%.2lf"),m_searchDates[i].m_total);
					m_searchDates[j].m_total = -1;
					tmp.PieNum ++;	
				}
			}
			if(tmp.PieName.IsEmpty())
			{
				switch(modal)
				{
				case 0:
					tmp.PieName = m_searchDates[i].m_checkModal == 1?_T("入库") :_T("出库");
					break;
				case 1:
					tmp.PieName = m_searchDates[i].m_material.m_name;
					break;
				case 2:
					tmp.PieName = m_searchDates[i].m_class.m_name;
					break;
				case 3:
					tmp.PieName = m_searchDates[i].m_userInfo.m_name;
					break;
				case 4:
					tmp.PieName = m_searchDates[i].m_time;
					break;
				default:
					tmp.PieName.Format(_T("%.2lf"),m_searchDates[i].m_total);
					break;
				}
			}
			if (!tmp.PieName.IsEmpty() )
			{
				tmp.PieNum = tmp.PieNum == 1 ? 1 : tmp.PieNum; 

				datas.push_back(tmp);
			}
		}
	}	
	m_pieChart_ctrl.FormatStaticDatas(datas);
}
void CDialog_Check_Stats::ShowEllipse()
{
	vector<PieData > datas;
	float NUM = 0.0000;
	for (int i=0;i< 21;i++)
	{
		PieData tmp;
		tmp.PieName.Format(_T("模块%d"),i + 1);
		tmp.PieNum = i*30 + i*i + 10;

		NUM += tmp.PieNum;
		datas.push_back(tmp);
	}

	m_pieChart_ctrl.FormatStaticDatas(datas);
}

void CDialog_Check_Stats::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_tBegin_ctrl.EnableWindow(BST_CHECKED == IsDlgButtonChecked( IDC_CHECK2 ));
	m_tEnd_ctrl.EnableWindow(BST_CHECKED == IsDlgButtonChecked( IDC_CHECK2 ));
}
