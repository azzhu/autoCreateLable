
// autoCreateLableDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CautoCreateLableDlg �Ի���



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


// CautoCreateLableDlg ��Ϣ�������

BOOL CautoCreateLableDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	//�����Լ���ӵ�
	AfxGetMainWnd()->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOSIZE | SWP_NOMOVE);

	m_jindu.SetRange(0, 100);
	m_jindu.SetStep(1);
	m_jindu.SetPos(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CautoCreateLableDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CautoCreateLableDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�Զ����ɱ�ǩ
void CautoCreateLableDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AfxGetMainWnd()->BeginWaitCursor();
	UpdateData();
	string m_path_ = m_path.GetBuffer(0);
	if (m_path_.length() == 0)
	{
		MessageBox("�������ļ���·����");
		return;
	}
	vector<string> filepath;
	az::getAllFilesPath(m_path_, filepath);
	if (filepath.size() == 0)
	{
		MessageBox("���ļ������ļ�����Ϊ0������·���Ƿ����");
		return;
	}

	//�����������
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
		string labelpath = m_getLabelPath(fn);	//��ȡ���·��
		string lb = m_getLabel(fn);	//��ȡ��ǩ
		labelfile << labelpath << " " << lb << endl;
		m_jindu.SetPos((int)(((i + 1) * 100) / filepath.size()));
		m_jindu.UpdateWindow();
	}
	labelfile.close();
	delete ind;

	AfxGetMainWnd()->EndWaitCursor();
	string info = "�ɹ�!\n" + labelfilename;
	MessageBox(info.c_str());
	m_jindu.SetPos(0);
}


// ����·����ȡ��ǩ
string CautoCreateLableDlg::m_getLabel(string path)
{
	int l = path.length();
	int st = -1, ed = -1, num = 0;
	for (int i = l - 1; i >= 0; i--)
	{
		if (path[i] == '\\' || path[i] == '/')	//�����ָܵ�ʱ��
		{
			if (i == 0 || (path[i - 1] != '\\' && path[i - 1] != '/'))	//ǰ��Ĳ��Ǹ�,����˫��·��
			{
				if (num == 0)	//��һ�γ��ָ�
				{
					ed = i - 1;	//��ǩ��ֹ��ָ��
					num++;
				}
				else
					if (num == 1)	//�ڶ��γ��ָܵ�ʱ��
					{
						st = i + 1;	//��ǩ��ʼ��ָ��
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


// �����ļ�����ȡ��ǰ�ļ������ļ���
string CautoCreateLableDlg::m_getCurrentPath(string filename)
{
	int l = filename.length();
	int num = -1;
	for (int i = l - 1; i >= 0; i--)
	{
		if (filename[i] == '\\' || filename[i] == '/')	//�����ָܵ�ʱ��
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


// ��ȡ����ġ�Ҫ��txt��д������·��
string CautoCreateLableDlg::m_getLabelPath(string filename)
{
	string st = m_path.GetBuffer(0);
	int l0 = st.length();
	int l1 = filename.length();
	
	return filename.substr(l0, l1 - l0 + 1);
}

//txt����
void CautoCreateLableDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	AfxGetMainWnd()->BeginWaitCursor();
	UpdateData();
	string m_path_ = m_path.GetBuffer(0);
	vector<string> allline;
	char oneline[1024] = { 0 };
	std::ifstream filein;
	filein.open(m_path_);
	if (!filein.is_open())
	{
		MessageBox("��txt��������·����");
		return;
	}
	while (filein.getline(oneline, sizeof(oneline)))
	{
		allline.push_back(oneline);
	}
	filein.close();

	//�����������
	int *ind = new int[allline.size()];
	int k = 0;
	while (k != allline.size())
	{
		ind[k] = k;
		k++;
	}
	az::random_sort(ind, allline.size());

	string savepath = m_path_.substr(0, m_path_.length() - 4) + "-���Һ�.txt";
	ofstream savetxt(savepath);
	if (!savetxt.is_open())
	{
		MessageBox("����txt·���������飡");
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
	string info = "�ɹ�!\n" + savepath;
	MessageBox(info.c_str());
	m_jindu.SetPos(0);
}

//ͼ��������
void CautoCreateLableDlg::OnBnClickedButton3()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		MessageBox("�������ļ���·����");
		return;
	}
	vector<string> filepath;
	az::getAllFilesPath(m_path_, filepath);
	if (filepath.size() == 0)
	{
		MessageBox("���ļ������ļ�����Ϊ0������·���Ƿ����");
		return;
	}
	if (w <= 0 || w > 1000 ||
		h <= 0 || h > 1000)
	{
		MessageBox("���Ӧ����0С��1000��");
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
	string info = "������ͼ��" + to_string(filepath.size()) + "��\n" +
		"��ͼ���ļ����У�" + to_string(notpicnum) + "��\n" +
		"����ʱ��" + to_string((tim_e - tim_s) / 1000) + "��";
	MessageBox(info.c_str());
	m_jindu.SetPos(0);
}
