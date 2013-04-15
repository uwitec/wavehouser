// CDialog_Piechart.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Piechart.h"
#include <math.h>      
//#include "afxdialogex.h"


#define M_PI     3.14159265358979323846
#define ER(x,y)  abs(fabs(x*x + y*y))  //直角第三边
// CDialog_Piechart 对话框

IMPLEMENT_DYNAMIC(CDialog_Piechart, CDialog)

CDialog_Piechart::CDialog_Piechart(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Piechart::IDD, pParent)
{
	m_AreaBkColor = RGB(000,000,000);

	GetNormalFont(m_TextFont);
	GetNormalFont(m_TextFont2,12,FW_BOLD);
}

CDialog_Piechart::~CDialog_Piechart()
{
	m_TextFont.DeleteObject();
	m_TextFont2.DeleteObject();
}

void CDialog_Piechart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog_Piechart, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_Piechart::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDialog_Piechart 消息处理程序

BOOL CDialog_Piechart::OnInitDialog()
{
	CDialog::OnInitDialog();
	

	return TRUE;
}

void CDialog_Piechart::SetEPos()
{
	if(m_EllipseRect.IsRectEmpty())
	{
		GetClientRect(m_EllipseRect);
		m_EllipseRect.top += 50;
		m_EllipseRect.left = m_EllipseRect.top;
		m_EllipseRect.bottom -= 50;
		m_EllipseRect.right = m_EllipseRect.bottom;
	}
	if(m_DetaiRect.IsRectEmpty())
	{
		GetClientRect(m_DetaiRect);
		m_DetaiRect.top += 50;
		m_DetaiRect.left = m_DetaiRect.top + m_EllipseRect.right + 50;
		m_DetaiRect.bottom -= 50;
		m_DetaiRect.right = m_DetaiRect.right - 50;
	}

	m_OPoint.x = ( m_EllipseRect.right - m_EllipseRect.left ) / 2 + m_EllipseRect.left;
	m_OPoint.y = ( m_EllipseRect.bottom - m_EllipseRect.top ) / 2 + m_EllipseRect.top;

	m_R = ER((float)(m_OPoint.x - m_EllipseRect.left) ,(float )(m_OPoint.y - m_EllipseRect.top));

	m_EllipseR = ( m_EllipseRect.right - m_EllipseRect.left ) / 2;   //半径

}
void CDialog_Piechart::SetEPos(const CRect &ellipseRect,const CRect &detailRect)
{
	m_EllipseRect = ellipseRect;

	m_DetaiRect = detailRect;

	m_OPoint.x = ( m_EllipseRect.right - m_EllipseRect.left ) / 2 + m_EllipseRect.left;
	m_OPoint.y = ( m_EllipseRect.bottom - m_EllipseRect.top ) / 2 + m_EllipseRect.top;

	m_R = ER((float)(m_OPoint.x - m_EllipseRect.left) ,(float )(m_OPoint.y - m_EllipseRect.top));

	m_EllipseR = ( m_EllipseRect.right - m_EllipseRect.left ) / 2;   //半径
}
void CDialog_Piechart::OnPaint()
{
	CPaintDC dc(this); // device context for painting
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CDialog::OnPaint()
	//if(!m_eRect.IsRectEmpty())
	//	dc.Ellipse(m_eRect);

	dc.FillSolidRect(&m_ClientRect,m_AreaBkColor);  //背景颜色
	dc.SelectObject(&m_TextFont);

	DoPaintEllipse(dc);
	DoPaintDetail(dc);
}

void CDialog_Piechart::DoPaintEllipse( CPaintDC &pDc )
{
	CPen pen;
	pen.CreatePen( PS_SOLID, 1,m_AreaBkColor);  //边框设置与背景同色
	HGDIOBJ hOldPen = pDc.SelectObject(pen);
	//pDc.Ellipse(&m_EllipseRect);
	CPoint oPoint(m_EllipseRect.bottom / 2,m_EllipseRect.right / 2);
	pDc.SetPixel(oPoint,m_AreaBkColor);  //画原点

	for (int i = 0 ;i<m_PieDatas.size() ;i++)
	{
		pen.DeleteObject();
		pen.CreatePen( PS_SOLID, 1,m_PieDatas[i].PieColor);
		pDc.SelectObject(pen);

		CBrush brush(m_PieDatas[i].PieColor);
		pDc.SelectObject(brush );
		pDc.Pie(&m_EllipseRect,m_PieDatas[i].pPoint.sPoint,m_PieDatas[i].pPoint.ePoint);

		brush.DeleteObject();
	}
	pDc.SelectObject(hOldPen);
	pen.DeleteObject();
}

void CDialog_Piechart::DoPaintDetail( CPaintDC &pDc )
{
	//25*25
	CRect rectTmp(m_DetaiRect.left,m_DetaiRect.top,m_DetaiRect.left + 25,m_DetaiRect.top + 25);
	CRect rectTextTmp(rectTmp.right + 5,rectTmp.top,m_DetaiRect.right,rectTmp.top + 14);
	CRect rectPercenTmp(rectTextTmp.left,rectTextTmp.bottom + 1,rectTextTmp.right,rectTextTmp.bottom + 14);
	CRect rectNumTmp(rectPercenTmp.left + 35,rectPercenTmp.top,rectPercenTmp.right + 40,rectPercenTmp.bottom );

	pDc.SetBkColor(m_AreaBkColor);
	pDc.SetTextColor(RGB(0,0,0));

	CString ItemPerTmp = _T("");
	float tmp ;
	pDc.SetBkMode(TRANSPARENT);
	for(int i = 0 ;i < m_PieDatas.size() ;i++)
	{
		CBrush brushTmp(m_PieDatas[i].PieColor);
		pDc.FillRect(rectTmp,&brushTmp);	
		//ItemPerTmp.Format(_T("%s(%d)"),m_PieDatas[i].PieName,m_PieDatas[i].PieNum);
		//pDc.DrawText(ItemPerTmp,ItemPerTmp.GetLength(),rectTextTmp,DT_LEFT | DT_VCENTER );
		pDc.DrawText(m_PieDatas[i].PieName,m_PieDatas[i].PieName.GetLength(),rectTextTmp,DT_LEFT | DT_VCENTER );

		int tmpi = m_PieDatas[i].PiePer * 10000;
		float tmpf = tmpi / 100.0;
		ItemPerTmp.Format(_T("%.1f%%"),tmpf);
		if(m_PieDatas.size() == 1)
		{
			ItemPerTmp = _T("100%");
		}

		pDc.SelectObject(m_TextFont2);
		pDc.DrawText(ItemPerTmp,ItemPerTmp.GetLength(),rectPercenTmp,DT_LEFT | DT_VCENTER  );

		pDc.SelectObject(m_TextFont);
		ItemPerTmp.Format(_T("(%d)"),m_PieDatas[i].PieNum );
		pDc.DrawText(ItemPerTmp,ItemPerTmp.GetLength(),rectNumTmp,DT_LEFT | DT_VCENTER  );
		rectTmp.top = rectTmp.bottom + 5;
		rectTmp.bottom = rectTmp.top + 25;

		rectTextTmp.top = rectTmp.top ;
		rectTextTmp.bottom = rectTextTmp.top + 14  ;

		rectPercenTmp.top = rectTextTmp.bottom + 1;
		rectPercenTmp.bottom = rectPercenTmp.top + 14;

		rectNumTmp.top = rectPercenTmp.top ;
		rectNumTmp.bottom = rectPercenTmp.bottom ;
	}
}


void CDialog_Piechart::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDialog_Piechart::FormatStaticDatas( const vector<PieData > &dates )
{
	SortDates(dates);

	m_DataNum = 0;
	
	for (int i= 0;i<m_PieDatas.size();i++)
	{
		m_DataNum += m_PieDatas[i].PieNum;
	}

	float tmpf = 0;
	float iAngleTmp = 360;
	float maxAngle = 0;
	int maxAlgleIndex = 0;
	for (int i=0 ;i<m_PieDatas.size();i++)
	{
		if(i != m_PieDatas.size() - 1)
		{
			m_PieDatas[i].PiePer = m_PieDatas[i].PieNum /(float)m_DataNum;
			int tmpi = m_PieDatas[i].PiePer * 10000;
			float tmpfs = tmpi / 10000.0;
			m_PieDatas[i].PiePer = tmpfs;
			tmpf += m_PieDatas[i].PiePer ;

			m_PieDatas[i].PicAngle = m_PieDatas[i].PiePer * 360 ;//百分比转角度
			m_PieDatas[i].PicAngle = m_PieDatas[i].PicAngle < 5? 5:m_PieDatas[i].PicAngle;
			iAngleTmp -= m_PieDatas[i].PicAngle;
			if(maxAngle < m_PieDatas[i].PicAngle)
			{
				maxAngle = m_PieDatas[i].PicAngle;
				maxAlgleIndex = i;
			}
		}
		else
		{
			m_PieDatas[i].PiePer = 1 - tmpf;
			if(iAngleTmp >= 5)
			{
				m_PieDatas[i].PicAngle = iAngleTmp;
			}
			else
			{
				m_PieDatas[i].PicAngle = 5;
				m_PieDatas[maxAlgleIndex].PicAngle = m_PieDatas[maxAlgleIndex].PicAngle + iAngleTmp - 5;
			}
		}
	}

	iAngleTmp = 360;
	CPoint sPoint(m_EllipseRect.top,m_EllipseRect.left);

	for (int i= 0;i<m_PieDatas.size();i++)
	{
		PiePoint tmp;
		float tmpi ;
		tmp.sPoint = i == 0 ? sPoint : m_PieDatas[i-1].pPoint.ePoint;
		if( i == m_PieDatas.size() - 1)
		{
			tmp.ePoint = sPoint;
			m_PieDatas[i].pPoint = tmp;
			m_PieDatas[i].PicAngle = iAngleTmp ;//百分比转角度
			break;
		}

		m_PieDatas[i].PicAngle = m_PieDatas[i].PiePer * 360 ;//百分比转角度
		m_PieDatas[i].PicAngle = m_PieDatas[i].PicAngle < 5? 5:m_PieDatas[i].PicAngle;
		iAngleTmp -= m_PieDatas[i].PicAngle;

		if(iAngleTmp >= 0 && iAngleTmp < 90)  //top边框
		{			
			tmp.ePoint.y = m_EllipseRect.top;
			if (iAngleTmp <= 45)
			{
				tmp.ePoint.x = m_EllipseR - m_EllipseR * tan(M_PI *(45 - iAngleTmp)/180);
			}
			else
			{
				tmpi = abs(tan(M_PI *(iAngleTmp - 45)/180));
				tmp.ePoint.x = m_EllipseR + m_EllipseR * tmpi;
			}
			tmp.ePoint.x += sPoint.x;
		}
		else if(iAngleTmp >= 90 && iAngleTmp < 180) //right 边框
		{
			tmp.ePoint.x = m_EllipseRect.right;
			if (iAngleTmp - 90 <= 45)
			{
				tmp.ePoint.y = m_EllipseR - m_EllipseR * tan(M_PI *(135 - iAngleTmp)/180);
			}
			else
			{
				tmpi = abs(tan(M_PI *(iAngleTmp - 135)/180));
				tmp.ePoint.y = m_EllipseR + m_EllipseR * tmpi;
			}
			tmp.ePoint.y += sPoint.y;
		}
		else if (iAngleTmp >= 180 && iAngleTmp < 270)  //bottom 边框
		{
			tmp.ePoint.y = m_EllipseRect.bottom;
			if (iAngleTmp - 180 <= 45)
			{
				tmp.ePoint.x = m_EllipseR + m_EllipseR * tan(M_PI *(225 - iAngleTmp)/180);
			}
			else
			{
				tmpi = abs(tan(M_PI *(iAngleTmp - 225)/180));
				tmp.ePoint.x = m_EllipseR - m_EllipseR * tmpi;
			}
			tmp.ePoint.x += sPoint.x;
		}
		else   //left 边框
		{
			tmp.ePoint.x = m_EllipseRect.left;
			if (iAngleTmp - 270 <= 45)
			{
				tmp.ePoint.y = m_EllipseR + m_EllipseR * tan(M_PI *(315 - iAngleTmp)/180);
			}
			else
			{
				tmpi = abs(tan(M_PI *(iAngleTmp - 315)/180));
				tmp.ePoint.y = m_EllipseR - m_EllipseR * tmpi;
			}
			tmp.ePoint.y += sPoint.y;
		}

		m_PieDatas[i].pPoint = tmp;
	}
}

void CDialog_Piechart::SortDates( const vector<PieData > &dates )
{
	if(dates.size() <= 10)
	{
		m_PieDatas = dates;
		for (int i = 0; i < m_PieDatas.size(); i ++)
		{
			m_PieDatas[i].PieColor = RGB(25 * i * 10,21 * i * 5,50 * (i+1) * 40);
		}

		return;
	}

	vector<PieData> tmp = dates;
	vector<PieData>::iterator delIndex;
	int maxNum = 0;
	int nNum = 0;
	int index = 0;

	for (int i=0;i < 10 ; i++)
	{
		PieData tmpP;
		if(i < 9)
		{
			nNum = 0;
			delIndex = tmp.begin();
			for (int ii = 0; ii < tmp.size(); ii ++)
			{
				if(nNum < tmp[ii].PieNum)
				{
					index = ii;

					nNum = tmp[ii].PieNum;
				}
			}

			tmpP = tmp[index];
			nNum += tmpP.PieNum;
			tmp.erase(delIndex + index);
		}
		tmpP.PieColor = RGB(25 * i * 10,21 * i * 5,50 * (i+1) * 40);
		m_PieDatas.push_back(tmpP);
	}

	for (int i = 0; i < dates.size(); i ++)
	{
		if(nNum <= 0)
			nNum += dates[i].PieNum;
		else
			nNum -= dates[i].PieNum;
	}

	m_PieDatas[9].PieNum = nNum;
	m_PieDatas[9].PieName = _T("其他");
}

