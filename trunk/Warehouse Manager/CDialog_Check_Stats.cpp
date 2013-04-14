// CDialog_Check_Stats.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Check_Stats.h"
#include "afxdialogex.h"


// CDialog_Check_Stats 对话框

IMPLEMENT_DYNAMIC(CDialog_Check_Stats, CDialogEx)

CDialog_Check_Stats::CDialog_Check_Stats(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialog_Check_Stats::IDD, pParent)
{

}

CDialog_Check_Stats::~CDialog_Check_Stats()
{
}

void CDialog_Check_Stats::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_tBegin_ctrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_tEnd_ctrl);
	DDX_Control(pDX, IDC_STATIC_S, m_pieChart_ctrl);
}


BEGIN_MESSAGE_MAP(CDialog_Check_Stats, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_Check_Stats::OnBnClickedSearchBtn)
END_MESSAGE_MAP()


// CDialog_Check_Stats 消息处理程序

BOOL CDialog_Check_Stats::OnInitDialog()
{
	CDialog::OnInitDialog();
	
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
	return TRUE;
}
void CDialog_Check_Stats::OnBnClickedSearchBtn()
{
}