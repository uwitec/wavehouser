// Warehouse ManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Warehouse Manager.h"
#include "Warehouse ManagerDlg.h"
#include "CDialog_Update.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CWarehouseManagerDlg �Ի���




CWarehouseManagerDlg::CWarehouseManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWarehouseManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_MaterialList = NULL;
	m_MaterialStats = NULL;
	m_checkLisk = NULL;
	m_checkStats = NULL;
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


// CWarehouseManagerDlg ��Ϣ�������

BOOL CWarehouseManagerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_NORMAL);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWarehouseManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CWarehouseManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CWarehouseManagerDlg::OnCompanyBtn()
{
	// TODO: �ڴ���������������
	CDialog_Company dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnUserInfoBtn()
{
	// TODO: �ڴ���������������
	CDialog_UserInfo dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnMaterialBtn()
{
	// TODO: �ڴ���������������
	CDialog_Material dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnWareHouseBtn()
{
	// TODO: �ڴ���������������
	CDialog_WareHouse dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnAddMatrtial()
{
	// TODO: �ڴ���������������
	CDialog_Material dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnEditMaterial()
{
	// TODO: �ڴ���������������
	CDialog_Material dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnSearchMaterial()
{
	// TODO: �ڴ���������������

	if(m_MaterialList == NULL)
	{
		m_MaterialList = new CDialog_Material_List(this);
		m_MaterialList->Create(IDD_DLG_MATERIAL_LIST);
		m_MaterialList->SetParent(this);//����dialog1Ϊ������
		m_MaterialList->ShowWindow(SW_HIDE);
	}
	CDialog_Update::UpdateDlg(m_MaterialList);
}


void CWarehouseManagerDlg::OnSearchMaterialState()
{
	// TODO: �ڴ���������������
	if(m_MaterialStats == NULL)
	{
		m_MaterialStats = new CDialog_Check_Stats();
		m_MaterialStats->Create(IDD_DLG_CHECK_STATS);
		m_MaterialStats->SetParent(this);//����dialog1Ϊ������
		m_MaterialStats->ShowWindow(SW_HIDE);
	}
	CDialog_Update::UpdateDlg(m_MaterialStats);
}


void CWarehouseManagerDlg::OnExit()
{
	// TODO: �ڴ���������������
	OnCancel();
}

void CWarehouseManagerDlg::OnAddBuyBtn()
{
	// TODO: �ڴ���������������
	CDialog_Check dlg;
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnAddPayBtn()
{
	// TODO: �ڴ���������������
	CDialog_Check dlg(FALSE);
	dlg.DoModal();
}


void CWarehouseManagerDlg::OnCheckSearchBtn()
{
	// TODO: �ڴ���������������
	if(m_checkLisk == NULL)
	{
		m_checkLisk = new CDialog_Check_List(this);
		m_checkLisk->Create(IDD_DLG_CHECK_LIST);
		m_checkLisk->SetParent(this);//����dialog1Ϊ������
		m_checkLisk->ShowWindow(SW_HIDE);
	}
	CDialog_Update::UpdateDlg(m_checkLisk);
}


void CWarehouseManagerDlg::OnCheckStats()
{
	// TODO: �ڴ���������������
	if(m_checkStats == NULL)
	{
		m_checkStats = new CDialog_Check_Stats();
		m_checkStats->Create(IDD_DLG_CHECK_STATS);
		m_checkStats->SetParent(this);//����dialog1Ϊ������
		m_checkStats->ShowWindow(SW_HIDE);
	}
	CDialog_Update::UpdateDlg(m_checkStats);
}


void CWarehouseManagerDlg::OnOutM()
{
	// TODO: �ڴ���������������
}


void CWarehouseManagerDlg::OnOutUser()
{
	// TODO: �ڴ���������������
}


void CWarehouseManagerDlg::OnOutCheck()
{
	// TODO: �ڴ���������������
}


void CWarehouseManagerDlg::OnSetSystem()
{
	// TODO: �ڴ���������������
}


void CWarehouseManagerDlg::OnHelp()
{
	// TODO: �ڴ���������������
}


void CWarehouseManagerDlg::OnAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg dlg;
	dlg.DoModal();
}
