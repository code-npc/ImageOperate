﻿#pragma once
#include "ImageProcessor.h"

// CImageOperateDlg 对话框
class CImageOperateDlg : public CDialogEx
{
public:
	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEOPERATE_DIALOG };
#endif


public:
	CImageOperateDlg(CWnd* pParent = nullptr);	// 标准构造函数

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	afx_msg HCURSOR OnQueryDragIcon();

	// 消息映射声明
	DECLARE_MESSAGE_MAP()



protected:
	ImageProcessor image_processor;   // 图像处理对象
	CStatic image_ontrol;           // 图片显示控件
	CString image_path;           // 当前加载的图像路径
	void display();
public:
	afx_msg void OnBnClickedOpenImage();  // 打开图片按钮事件
	afx_msg void OnBnClickedSaveImage();  // 保存图片按钮事件
	afx_msg void OnBnClickedZoomIn();     // 缩放按钮事件
	afx_msg void OnBnClickedZoomOut();
	afx_msg void OnBnClickedRotate();     // 旋转按钮事件
	afx_msg void OnBnClickedFlipH();      // 水平翻转
	afx_msg void OnBnClickedFlipV();      // 垂直翻转
	afx_msg void OnPaint();
};
