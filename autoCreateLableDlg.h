
// autoCreateLableDlg.h : 头文件
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


// CautoCreateLableDlg 对话框
class CautoCreateLableDlg : public CDialogEx
{
// 构造
public:
	CautoCreateLableDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_AUTOCREATELABLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	// 样本文件夹
	CString m_path;
	BOOL m_notrandom;
	// 根据路径获取标签
	string m_getLabel(string path);
	// 根据文件名获取当前文件所在文件夹
	string m_getCurrentPath(string filename);
	// 获取后面的、要在txt里写入的相对路径
	string m_getLabelPath(string filename);
	afx_msg void OnBnClickedButton2();
	// 批处理图像时是否转灰度
	BOOL m_gray;
	// 宽度
	CString m_w;
	// 高度
	CString m_h;
	afx_msg void OnBnClickedButton3();
	CProgressCtrl m_jindu;
};
