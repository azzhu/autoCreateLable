
// autoCreateLableDlg.h : ͷ�ļ�
//

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace std;
#include <vector>
#include <fstream>
#include <iostream>
#include "F:\azcaffevs13\Process_preFrame\myfile\zqjtools.hpp"

#pragma once


// CautoCreateLableDlg �Ի���
class CautoCreateLableDlg : public CDialogEx
{
// ����
public:
	CautoCreateLableDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AUTOCREATELABLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	// �����ļ���
	CString m_path;
	BOOL m_notrandom;
	// ����·����ȡ��ǩ
	string m_getLabel(string path);
	// �����ļ�����ȡ��ǰ�ļ������ļ���
	string m_getCurrentPath(string filename);
	// ��ȡ����ġ�Ҫ��txt��д������·��
	string m_getLabelPath(string filename);
	afx_msg void OnBnClickedButton2();
	// ������ͼ��ʱ�Ƿ�ת�Ҷ�
	BOOL m_gray;
	// ���
	CString m_w;
	// �߶�
	CString m_h;
	afx_msg void OnBnClickedButton3();
	CProgressCtrl m_jindu;
};
