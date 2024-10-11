#pragma once
#include "ImageProcessor.h"

// CImageOperateDlg 对话框
class CImageOperateDlg : public CDialogEx
{
// 构造
public:
	CImageOperateDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEOPERATE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	CImageProcessor m_imgProcessor;   // 图像处理对象
	CStatic m_imageControl;           // 图片显示控件
	CString m_strImagePath;           // 当前加载的图像路径
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOpenImage();  // 打开图片按钮事件
	afx_msg void OnBnClickedSaveImage();  // 保存图片按钮事件
	afx_msg void OnBnClickedZoomIn();     // 缩放按钮事件
	afx_msg void OnBnClickedZoomOut();
	afx_msg void OnBnClickedRotate();     // 旋转按钮事件
	afx_msg void OnBnClickedFlipH();      // 水平翻转
	afx_msg void OnBnClickedFlipV();      // 垂直翻转
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
