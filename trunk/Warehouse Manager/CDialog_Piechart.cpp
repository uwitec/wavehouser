// CDialog_Piechart.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Piechart.h"
#include "afxdialogex.h"


// CDialog_Piechart �Ի���

IMPLEMENT_DYNAMIC(CDialog_Piechart, CDialog)

CDialog_Piechart::CDialog_Piechart(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Piechart::IDD, pParent)
{
}

CDialog_Piechart::~CDialog_Piechart()
{
}

void CDialog_Piechart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog_Piechart, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_Piechart::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDialog_Piechart ��Ϣ�������

BOOL CDialog_Piechart::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	return TRUE;
}

void CDialog_Piechart::SetEPos()
{
	if(m_eRect.IsRectEmpty())
	{
		GetClientRect(m_eRect);
		m_eRect.top += 50;
		m_eRect.left = m_eRect.top;
		m_eRect.bottom -= 50;
		m_eRect.right = m_eRect.bottom;
	}
}
void CDialog_Piechart::SetEPos(const CRect &pos)
{
	m_eRect = pos;
}
void CDialog_Piechart::OnPaint()
{
	CPaintDC dc(this); // device context for painting
		// TODO: �ڴ˴������Ϣ����������
		// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	if(!m_eRect.IsRectEmpty())
		dc.Ellipse(m_eRect);

	//dc.Pie(
}



void CDialog_Piechart::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
