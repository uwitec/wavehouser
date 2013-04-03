// CDialog_Material.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_Material.h"


// CDialog_Material 对话框

IMPLEMENT_DYNAMIC(CDialog_Material, CDialog)

CDialog_Material::CDialog_Material(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_Material::IDD, pParent)
{

}

CDialog_Material::~CDialog_Material()
{
}

void CDialog_Material::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog_Material, CDialog)
END_MESSAGE_MAP()


// CDialog_Material 消息处理程序
