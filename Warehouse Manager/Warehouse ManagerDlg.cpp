// Warehouse ManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "Warehouse ManagerDlg.h"
#include "CDialog_Update.h"
#include "CDialog_Login.h"
//#include "CControl_DB.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DWORD WINAPI LoginThread(LPVOID lpParam)
{
	CDialog_Login pInfo;
	
	return pInfo.DoModal();
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CWarehouseManagerDlg 对话框




CWarehouseManagerDlg::CWarehouseManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWarehouseManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_MaterialList = NULL;
	m_MaterialList_out = NULL;
	m_MaterialStats = NULL;
	m_checkList = NULL;
	m_checkList_out = NULL;
	m_checkStats = NULL;
	m_UserList = NULL;
}

void CWarehouseManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWarehouseManagerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_32775, &CWarehouseManagerDlg::OnCompanyBtn)
	ON_COMMAND(ID_32772, &CWarehouseManagerDlg::OnUserInfoBtn)
	ON_COMMAND(ID_32773, &CWarehouseManagerDlg::OnMaterialBtn)
	ON_COMMAND(ID_32771, &CWarehouseManagerDlg::OnWareHouseBtn)
	ON_COMMAND(ID_32777, &CWarehouseManagerDlg::OnAddMatrtial)
	ON_COMMAND(ID_32778, &CWarehouseManagerDlg::OnEditMaterial)
	ON_COMMAND(ID_32779, &CWarehouseManagerDlg::OnSearchMaterial)
	ON_COMMAND(ID_32780, &CWarehouseManagerDlg::OnSearchMaterialState)
	ON_COMMAND(ID_32776, &CWarehouseManagerDlg::OnExit)
	ON_COMMAND(ID_32781, &CWarehouseManagerDlg::OnAddBuyBtn)
	ON_COMMAND(ID_32793, &CWarehouseManagerDlg::OnAddPayBtn)
	ON_COMMAND(ID_32782, &CWarehouseManagerDlg::OnCheckSearchBtn)
	ON_COMMAND(ID_32791, &CWarehouseManagerDlg::OnCheckStats)
	ON_COMMAND(ID_32785, &CWarehouseManagerDlg::OnOutM)
	ON_COMMAND(ID_32786, &CWarehouseManagerDlg::OnOutUser)
	ON_COMMAND(ID_32787, &CWarehouseManagerDlg::OnOutCheck)
	ON_COMMAND(ID_32788, &CWarehouseManagerDlg::OnSetSystem)
	ON_COMMAND(ID_32790, &CWarehouseManagerDlg::OnHelp)
	ON_COMMAND(ID_32789, &CWarehouseManagerDlg::OnAbout)
END_MESSAGE_MAP()


// CWarehouseManagerDlg 消息处理程序

BOOL CWarehouseManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	ShowWindow(SW_NORMAL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWarehouseManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWarehouseManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CWarehouseManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWarehouseManagerDlg::OnCompanyBtn()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_Company dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnUserInfoBtn()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_UserInfo dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnMaterialBtn()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_Material dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnWareHouseBtn()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_WareHouse dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnAddMatrtial()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_Material dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnEditMaterial()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_Material dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnSearchMaterial()
{
	// TODO: 在此添加命令处理程序代码

	if(m_MaterialList == NULL)
	{
		m_MaterialList = new CDialog_Material_List();
		m_MaterialList->Create(IDD_DLG_MATERIAL_LIST);
		m_MaterialList->SetParent(this);//设置dialog1为父窗口
		m_MaterialList->ShowWindow(SW_HIDE);
	}
	CDialog_Update::UpdateDlg(m_MaterialList);
}


void CWarehouseManagerDlg::OnSearchMaterialState()
{
	// TODO: 在此添加命令处理程序代码
	if(m_MaterialStats == NULL)
	{
		m_MaterialStats = new CDialog_Check_Stats();
		m_MaterialStats->Create(IDD_DLG_CHECK_STATS);
		m_MaterialStats->SetParent(this);//设置dialog1为父窗口
		m_MaterialStats->ShowWindow(SW_HIDE);
	}
	CDialog_Update::UpdateDlg(m_MaterialStats);
}


void CWarehouseManagerDlg::OnExit()
{
	// TODO: 在此添加命令处理程序代码
	OnCancel();
}

void CWarehouseManagerDlg::OnAddBuyBtn()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_Check dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnAddPayBtn()
{
	// TODO: 在此添加命令处理程序代码
	CDialog_Check dlg(FALSE);
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnCheckSearchBtn()
{
	// TODO: 在此添加命令处理程序代码
	if(m_checkList == NULL)
	{
		m_checkList = new CDialog_Check_List();
		m_checkList->Create(IDD_DLG_CHECK_LIST);
		m_checkList->SetParent(this);//设置dialog1为父窗口
		m_checkList->ShowWindow(SW_HIDE);
	}
	CDialog_Update::UpdateDlg(m_checkList);
}


void CWarehouseManagerDlg::OnCheckStats()
{
	// TODO: 在此添加命令处理程序代码
	if(m_checkStats == NULL)
	{
		m_checkStats = new CDialog_Check_Stats();
		m_checkStats->Create(IDD_DLG_CHECK_STATS);
		m_checkStats->SetParent(this);//设置dialog1为父窗口
		m_checkStats->ShowWindow(SW_HIDE);
	}
	CDialog_Update::UpdateDlg(m_checkStats);
}


void CWarehouseManagerDlg::OnOutM()
{
	// TODO: 在此添加命令处理程序代码
	
	if(m_MaterialList_out == NULL)
	{
		m_MaterialList_out = new CDialog_Material_List(true);
		m_MaterialList_out->Create(IDD_DLG_MATERIAL_LIST);
		m_MaterialList_out->SetParent(this);//设置dialog1为父窗口
		m_MaterialList_out->ShowWindow(SW_HIDE);
	}
	CDialog_Update::UpdateDlg(m_MaterialList_out);
}


void CWarehouseManagerDlg::OnOutUser()
{
	// TODO: 在此添加命令处理程序代码
	if(m_UserList == NULL)
	{
		m_UserList = new CDialog_User_List(true);
		m_UserList->Create(IDD_DLG_USER_LIST);
		m_UserList->SetParent(this);//设置dialog1为父窗口
		m_UserList->ShowWindow(SW_HIDE);
	}
	CDialog_Update::UpdateDlg(m_UserList);
}


void CWarehouseManagerDlg::OnOutCheck()
{
	// TODO: 在此添加命令处理程序代码

	if(m_checkList_out == NULL)
	{
		m_checkList_out = new CDialog_Check_List(true);
		m_checkList_out->Create(IDD_DLG_CHECK_LIST);
		m_checkList_out->SetParent(this);//设置dialog1为父窗口
		m_checkList_out->ShowWindow(SW_HIDE);
	}
	CDialog_Update::UpdateDlg(m_checkList_out);
}


void CWarehouseManagerDlg::OnSetSystem()
{
	// TODO: 在此添加命令处理程序代码
}


void CWarehouseManagerDlg::OnHelp()
{
	// TODO: 在此添加命令处理程序代码
}


void CWarehouseManagerDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}

bool CWarehouseManagerDlg::LoginUser()
{
	//HANDLE tmpHandle = CreateThread(NULL,NULL,LoginThread,NULL,0,NULL);

	//WaitForSingleObject(tmpHandle,INFINITE);

	//DWORD result;
	//GetExitCodeThread(tmpHandle,&result);

	//CDialog_Login pInfo;

	//return pInfo.DoModal() == IDOK;
	//return result == IDOK;

	return true;
}
