#include "StdAfx.h"
#include "CEllipseStatic.h"
#include <math.h>      
CEllipseStatic::CEllipseStatic(void)
{
	m_AreaBkColor = RGB(000,000,000);

	GetNormalFont(m_TextFont);
	GetNormalFont(m_TextFont2,12,FW_BOLD);
}

CEllipseStatic::CEllipseStatic( vector<PieData > pieDatas )
{
	m_PieDatas = pieDatas;

	m_AreaBkColor = RGB(000,000,000);

	GetNormalFont(m_TextFont);
	GetNormalFont(m_TextFont2,12,FW_BOLD);
}

CEllipseStatic::~CEllipseStatic(void)
{
	m_TextFont.DeleteObject();
	m_TextFont2.DeleteObject();
}

BOOL CEllipseStatic::CreateEllipseStatic( HWND parenHwnd,CRect rectArea ,CPoint ellipsePoint , int ellipseWidth,CPoint detailPoint,int detailWidth ,vector<PieData > pieDatas)
{
	DWORD dwStyle = WS_CHILD | SS_NOTIFY;

	m_ParentHwnd = parenHwnd;

	m_RectArea = rectArea;

	m_PieDatas = pieDatas;

	LRESULT result = (LRESULT)Create(parenHwnd, rectArea, NULL,dwStyle);

	ShowWindow(SW_HIDE);

	GetClientRect(&m_ClientRect);

	if(ellipseWidth > rectArea.bottom - rectArea.top - ellipsePoint.x)
	{
		ellipseWidth =  rectArea.bottom - rectArea.top - ellipsePoint.x;
	}
	m_EllipseRect.top = ellipsePoint.x;
	m_EllipseRect.bottom =ellipsePoint.x + ellipseWidth;
	m_EllipseRect.left = ellipsePoint.y;
	m_EllipseRect.right = ellipsePoint.y + ellipseWidth;

	//if (detailWidth > rectArea.right - rectArea.left - m_EllipseRect.left - ellipseWidth)
	{
		detailWidth =  rectArea.right - rectArea.left - m_EllipseRect.left - ellipseWidth;
	}

	m_DetaiRect.left = detailPoint.x;
	m_DetaiRect.right = detailPoint.x + detailWidth;
	m_DetaiRect.top = detailPoint.y;
	m_DetaiRect.bottom = m_RectArea.bottom - m_RectArea.top - m_DetaiRect.top;

	m_OPoint.x = ( m_EllipseRect.right - m_EllipseRect.left ) / 2 + m_EllipseRect.left;
	m_OPoint.y = ( m_EllipseRect.bottom - m_EllipseRect.top ) / 2 + m_EllipseRect.top;

	m_R = ER((float)(m_OPoint.x - m_EllipseRect.left) ,(float )(m_OPoint.y - m_EllipseRect.top));

	m_EllipseR = ( m_EllipseRect.right - m_EllipseRect.left ) / 2;   //半径
	return result;
}

BOOL CEllipseStatic::CreateEllipseStatic( HWND parenHwnd,CRect rectArea ,CRect ellipseRect ,CRect detailRect)
{
	DWORD dwStyle = WS_CHILD | SS_NOTIFY;

	m_ParentHwnd = parenHwnd;

	m_RectArea = rectArea;

	LRESULT result = (LRESULT)Create(parenHwnd, rectArea, NULL,dwStyle);

	ShowWindow(SW_HIDE);

	GetClientRect(&m_ClientRect);
	
	m_EllipseRect = ellipseRect;

	m_DetaiRect = detailRect;

	m_OPoint.x = ( m_EllipseRect.right - m_EllipseRect.left ) / 2 + m_EllipseRect.left;
	m_OPoint.y = ( m_EllipseRect.bottom - m_EllipseRect.top ) / 2 + m_EllipseRect.top;

	m_R = ER((float)(m_OPoint.x - m_EllipseRect.left) ,(float )(m_OPoint.y - m_EllipseRect.top));

	m_EllipseR = ( m_EllipseRect.right - m_EllipseRect.left ) / 2;   //半径
	return result;
}

BOOL CEllipseStatic::CreateEllipseStatic( HWND parenHwnd,CRect rectArea,CRect ellipseRect ,CRect detailRect,vector<PieData > pieDatas )
{
	DWORD dwStyle = WS_CHILD | SS_NOTIFY;

	m_ParentHwnd = parenHwnd;

	m_RectArea = rectArea;

	m_PieDatas = pieDatas;

	LRESULT result = (LRESULT)Create(parenHwnd, rectArea, NULL,dwStyle);

	ShowWindow(SW_HIDE);

	GetClientRect(&m_ClientRect);

	m_EllipseRect = ellipseRect;

	m_DetaiRect = detailRect;

	m_OPoint.x = ( m_EllipseRect.right - m_EllipseRect.left ) / 2 + m_EllipseRect.left;
	m_OPoint.y = ( m_EllipseRect.bottom - m_EllipseRect.top ) / 2 + m_EllipseRect.top;

	m_R = ER((float)(m_OPoint.x - m_EllipseRect.left) ,(float )(m_OPoint.y - m_EllipseRect.top));

	m_EllipseR = ( m_EllipseRect.right - m_EllipseRect.left ) / 2;   //半径
	return result;
}

BOOL CEllipseStatic::ShowEllipseStatic(const bool &isShow /*= TRUE*/)
{
	if (!m_PieDatas.empty() && isShow)
	{
		ShowWindow(SW_SHOW);

		return TRUE;
	}

	return FALSE;
}

LRESULT CEllipseStatic::OnPaint( UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/ )
{
	CPaintDC pDc(m_hWnd);

	pDc.FillSolidRect(&m_ClientRect,m_AreaBkColor);  //背景颜色
	pDc.SelectFont(m_TextFont);

	DoPaintEllipse(pDc);
	DoPaintDetail(pDc);
	DoPaintDetail(pDc);

	return 0;
}

void CEllipseStatic::DoPaintEllipse( CPaintDC &pDc )
{
	CPen pen;
	pen.CreatePen( PS_SOLID, 1,m_AreaBkColor);  //边框设置与背景同色
	HPEN hOldPen = pDc.SelectPen(pen);
	pDc.Ellipse(&m_EllipseRect);
	CPoint oPoint(m_EllipseRect.bottom / 2,m_EllipseRect.right / 2);
	pDc.SetPixel(oPoint,m_AreaBkColor);  //画原点

	for (int i = 0 ;i<m_PieDatas.size() ;i++)
	{
		pen.DeleteObject();
		pen.CreatePen( PS_SOLID, 1,m_PieDatas[i].PieColor);
		pDc.SelectPen(pen);
		
		CBrush brush( ::CreateSolidBrush(m_PieDatas[i].PieColor));
		pDc.SelectBrush(brush );
		pDc.Pie(&m_EllipseRect,m_PieDatas[i].pPoint.sPoint,m_PieDatas[i].pPoint.ePoint);

		brush.DeleteObject();
	}
	pDc.SelectPen(hOldPen);
	pen.DeleteObject();
}

void CEllipseStatic::DoPaintDetail( CPaintDC &pDc )
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
	for(int i = 0 ;i < m_PieDatas.size() ;i++)
	{
		CBrush brushTmp=::CreateSolidBrush(m_PieDatas[i].PieColor);
		pDc.FillRect(rectTmp,brushTmp);	
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

		pDc.SelectFont(m_TextFont2);
		pDc.DrawText(ItemPerTmp,ItemPerTmp.GetLength(),rectPercenTmp,DT_LEFT | DT_VCENTER  );

		pDc.SelectFont(m_TextFont);
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

LRESULT CEllipseStatic::OnDestroy( UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/ )
{
	m_PieDatas.clear();

	return 0;
}

void CEllipseStatic::SetAreaBkColor( COLORREF areaBkColor,COLORREF ellipseBkColor,COLORREF detailBkColor )
{
	m_AreaBkColor = areaBkColor;
	m_EllipseBkColor = ellipseBkColor;
	m_DetailBkColor = detailBkColor;
}

void CEllipseStatic::FormatStaticPercen()
{
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
}
void CEllipseStatic::FormatStaticDatas()
{
	FormatStaticPercen();

	float iAngleTmp = 360;
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
		}

		m_PieDatas[i].pPoint = tmp;
	}
}

LRESULT CEllipseStatic::OnNcHitTest( UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/ )
{
	CRect rc;  
	POINT pt;  
	pt.x = GET_X_LPARAM(lParam);  
	pt.y = GET_Y_LPARAM(lParam);  
	GetClientRect(&rc);  
	ClientToScreen(&rc);  

	if(pt.y > (rc.top ))
	{
		return rc.PtInRect(pt) ? HTCAPTION : 0;  
	}
	else
	{
		return 1;
	}

}
