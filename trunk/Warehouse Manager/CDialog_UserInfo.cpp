// CDialog_UserInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_UserInfo.h"


// CDialog_UserInfo 对话框

IMPLEMENT_DYNAMIC(CDialog_UserInfo, CDialog)

CDialog_UserInfo::CDialog_UserInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_UserInfo::IDD, pParent)
{

}

CDialog_UserInfo::~CDialog_UserInfo()
{
}

void CDialog_UserInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog_UserInfo, CDialog)
END_MESSAGE_MAP()


// CDialog_UserInfo 消息处理程序
