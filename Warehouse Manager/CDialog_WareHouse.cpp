// CDialog_WareHouse.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "CDialog_WareHouse.h"
#include "afxdialogex.h"


// CDialog_WareHouse �Ի���

IMPLEMENT_DYNAMIC(CDialog_WareHouse, CDialog)

CDialog_WareHouse::CDialog_WareHouse(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog_WareHouse::IDD, pParent)
{

}

CDialog_WareHouse::~CDialog_WareHouse()
{
}

void CDialog_WareHouse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog_WareHouse, CDialog)
	ON_BN_CLICKED(IDC_BTB_SAVE, &CDialog_WareHouse::OnBnClickedBtbSave)
	ON_BN_CLICKED(IDC_BTB_QUIT, &CDialog_WareHouse::OnBnClickedBtbQuit)
END_MESSAGE_MAP()


// CDialog_WareHouse ��Ϣ�������


void CDialog_WareHouse::OnBnClickedBtbSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CDialog_WareHouse::OnBnClickedBtbQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
