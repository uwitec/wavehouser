#pragma once
#include "stdafx.h"

class CDialog_Update
{
public:

	CDialog_Update(void){};
	~CDialog_Update(void){};

private:
	static CDialog *m_newDlg;
	static CDialog *m_oldDlg;

public:
	static void UpdateDlg(CDialog *nowDlg)
	{
		if(m_oldDlg == NULL)
		{
			m_oldDlg = nowDlg;
			m_newDlg = nowDlg;

			nowDlg->ShowWindow(SW_SHOW);

			return;
		}
		if(m_newDlg->m_hWnd != nowDlg->m_hWnd)
		{
			m_oldDlg = m_newDlg;
			m_newDlg = nowDlg;
			if(m_newDlg != NULL)
			{
				m_newDlg->ShowWindow(SW_SHOW);
			}
			if(m_oldDlg != NULL)
			{
				m_oldDlg->ShowWindow(SW_HIDE);
			}
		}
		else
		{
			nowDlg->ShowWindow(SW_SHOW);
		}
	}
	
};


CDialog * CDialog_Update::m_newDlg = NULL;
CDialog * CDialog_Update::m_oldDlg = NULL;