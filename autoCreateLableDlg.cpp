
// autoCreateLableDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "autoCreateLable.h"
#include "autoCreateLableDlg.h"
#include "afxdialogex.h"

#include <cv.hpp>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CautoCreateLableDlg 对话框



CautoCreateLableDlg::CautoCreateLableDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CautoCreateLableDlg::IDD, pParent)
	, m_path(_T(""))
	, m_notrandom(FALSE)
	, m_gray(FALSE)
	, m_w(_T(""))
	, m_h(_T(""))
	, m_jindu()
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CautoCreateLableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_path);
	DDX_Check(pDX, IDC_CHECK1, m_notrandom);
	DDX_Check(pDX, IDC_CHECK2, m_gray);
	DDX_Text(pDX, IDC_EDIT2, m_w);
	DDX_Text(pDX, IDC_EDIT3, m_h);
	DDX_Control(pDX, IDC_PROGRESS2, m_jindu);
}

BEGIN_MESSAGE_MAP(CautoCreateLableDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CautoCreateLableDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CautoCreateLableDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CautoCreateLableDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CautoCreateLableDlg 消息处理程序

BOOL CautoCreateLableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	//下面自己添加的
	AfxGetMainWnd()->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOSIZE | SWP_NOMOVE);

	m_jindu.SetRange(0, 100);
	m_jindu.SetStep(1);
	m_jindu.SetPos(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CautoCreateLableDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CautoCreateLableDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CautoCreateLableDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//自动生成标签
void CautoCreateLableDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	AfxGetMainWnd()->BeginWaitCursor();
	UpdateData();
	string m_path_ = m_path.GetBuffer(0);
	if (m_path_.length() == 0)
	{
		MessageBox("请输入文件夹路径！");
		return;
	}
	vector<string> filepath;
	az::getAllFilesPath(m_path_, filepath);
	if (filepath.size() == 0)
	{
		MessageBox("改文件夹下文件总数为0，请检查路径是否错误！");
		return;
	}

	//生成随机序列
	int *ind = new int[filepath.size()];
	int k = 0;
	while (k != filepath.size())
	{
		ind[k] = k;
		k++;
	}
	if (!m_notrandom)
		az::random_sort(ind, filepath.size());

	string labelfilename = m_path_ + "\\label.txt";
	ofstream labelfile(labelfilename);
	for (int i = 0; i < filepath.size(); i++)
	{
		string fn = filepath[ind[i]];
		string labelpath = m_getLabelPath(fn);	//获取相对路径
		string lb = m_getLabel(fn);	//获取标签
		labelfile << labelpath << " " << lb << endl;
		m_jindu.SetPos((int)(((i + 1) * 100) / filepath.size()));
		m_jindu.UpdateWindow();
	}
	labelfile.close();
	delete ind;

	AfxGetMainWnd()->EndWaitCursor();
	string info = "成功!\n" + labelfilename;
	MessageBox(info.c_str());
	m_jindu.SetPos(0);
}


// 根据路径获取标签
string CautoCreateLableDlg::m_getLabel(string path)
{
	int l = path.length();
	int st = -1, ed = -1, num = 0;
	for (int i = l - 1; i >= 0; i--)
	{
		if (path[i] == '\\' || path[i] == '/')	//当出现杠的时候
		{
			if (i == 0 || (path[i - 1] != '\\' && path[i - 1] != '/'))	//前面的不是杠,避免双杠路径
			{
				if (num == 0)	//第一次出现杠
				{
					ed = i - 1;	//标签终止的指针
					num++;
				}
				else
					if (num == 1)	//第二次出现杠的时候
					{
						st = i + 1;	//标签开始的指针
						goto markkkk;
					}
			}

		}
	}

markkkk:
	if (st == -1 || ed == -1)
		return "error";
	else
		return path.substr(st, ed - st + 1);
}


// 根据文件名获取当前文件所在文件夹
string CautoCreateLableDlg::m_getCurrentPath(string filename)
{
	int l = filename.length();
	int num = -1;
	for (int i = l - 1; i >= 0; i--)
	{
		if (filename[i] == '\\' || filename[i] == '/')	//当出现杠的时候
		{
			num = i;
			break;
		}
	}
	if (num == -1)
		return "error";
	else
		return filename.substr(0, num + 1);
}


// 获取后面的、要在txt里写入的相对路径
string CautoCreateLableDlg::m_getLabelPath(string filename)
{
	string st = m_path.GetBuffer(0);
	int l0 = st.length();
	int l1 = filename.length();
	
	return filename.substr(l0, l1 - l0 + 1);
}

//txt打乱
void CautoCreateLableDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	AfxGetMainWnd()->BeginWaitCursor();
	UpdateData();
	string m_path_ = m_path.GetBuffer(0);
	vector<string> allline;
	char oneline[1024] = { 0 };
	std::ifstream filein;
	filein.open(m_path_);
	if (!filein.is_open())
	{
		MessageBox("打开txt错误，请检查路径！");
		return;
	}
	while (filein.getline(oneline, sizeof(oneline)))
	{
		allline.push_back(oneline);
	}
	filein.close();

	//生成随机序列
	int *ind = new int[allline.size()];
	int k = 0;
	while (k != allline.size())
	{
		ind[k] = k;
		k++;
	}
	az::random_sort(ind, allline.size());

	string savepath = m_path_.substr(0, m_path_.length() - 4) + "-打乱后.txt";
	ofstream savetxt(savepath);
	if (!savetxt.is_open())
	{
		MessageBox("保存txt路径出错，请检查！");
		return;
	}
	for (int i = 0; i < allline.size(); i++)
	{
		savetxt << allline[ind[i]] << endl;
		m_jindu.SetPos((int)(((i + 1) * 100) / allline.size()));
		m_jindu.UpdateWindow();
	}
	savetxt.close();
	delete ind;

	AfxGetMainWnd()->EndWaitCursor();
	string info = "成功!\n" + savepath;
	MessageBox(info.c_str());
	m_jindu.SetPos(0);
}

//图像批处理
void CautoCreateLableDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	AfxGetMainWnd()->BeginWaitCursor();
	UpdateData();
	long tim_s, tim_e;
	tim_s = az::getTime();

	string m_path_ = m_path.GetBuffer(0);
	string m_w_ = m_w.GetBuffer(0);
	string m_h_ = m_h.GetBuffer(0);
	int w = atoi(m_w_.c_str());
	int h = atoi(m_h_.c_str());
	if (m_path_.length() == 0)
	{
		MessageBox("请输入文件夹路径！");
		return;
	}
	vector<string> filepath;
	az::getAllFilesPath(m_path_, filepath);
	if (filepath.size() == 0)
	{
		MessageBox("改文件夹下文件总数为0，请检查路径是否错误！");
		return;
	}
	if (w <= 0 || w > 1000 ||
		h <= 0 || h > 1000)
	{
		MessageBox("宽高应大于0小于1000！");
		return;
	}

	cv::Mat temp;
	int notpicnum = 0;
	for (int i = 0; i < filepath.size(); i++)
	{
		temp = cv::imread(filepath[i]);
		if (temp.empty())
		{
			notpicnum++;
		}
		else
		{
			if (m_gray && (temp.channels() != 1))
				cv::cvtColor(temp, temp, CV_BGR2GRAY);

			temp = az::imgto(&temp, w, h);
			cv::imwrite(filepath[i], temp);
		}
		m_jindu.SetPos((int)(((i + 1) * 100) / filepath.size()));
		m_jindu.UpdateWindow();
	}
	tim_e = az::getTime();
	
	AfxGetMainWnd()->EndWaitCursor();
	string info = "共处理图像：" + to_string(filepath.size()) + "张\n" +
		"非图像文件共有：" + to_string(notpicnum) + "个\n" +
		"共用时：" + to_string((tim_e - tim_s) / 1000) + "秒";
	MessageBox(info.c_str());
	m_jindu.SetPos(0);
}
