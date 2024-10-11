#include "pch.h"
#include "framework.h"
#include "ImageOperate.h"
#include "ImageOperateDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CImageOperateDlg 对话框

CImageOperateDlg::CImageOperateDlg(CWnd* pParent /*=nullptr*/): CDialogEx(IDD_IMAGEOPERATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageOperateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CImageOperateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// TODO: 在此添加额外的初始化代码


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImageOperateDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CImageOperateDlg::OnPaint()
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
HCURSOR CImageOperateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BEGIN_MESSAGE_MAP(CImageOperateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CImageOperateDlg::OnBnClickedOpenImage)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CImageOperateDlg::OnBnClickedSaveImage)
	ON_BN_CLICKED(IDC_BTN_ZOOM_IN, &CImageOperateDlg::OnBnClickedZoomIn)
	ON_BN_CLICKED(IDC_BTN_ZOOM_OUT, &CImageOperateDlg::OnBnClickedZoomOut)
	ON_BN_CLICKED(IDC_BTN_ROTATE, &CImageOperateDlg::OnBnClickedRotate)
	ON_BN_CLICKED(IDC_BTN_FLIP_H, &CImageOperateDlg::OnBnClickedFlipH)
	ON_BN_CLICKED(IDC_BTN_FLIP_V, &CImageOperateDlg::OnBnClickedFlipV)
END_MESSAGE_MAP()


void CImageOperateDlg::OnBnClickedOpenImage()
{
	// 使用 CFileDialog 打开图像
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("图片文件 (*.jpg; *.png; *.bmp)|*.jpg; *.png; *.bmp||"));
	if (dlg.DoModal() == IDOK)
	{
		m_strImagePath = dlg.GetPathName();
		//m_imgProcessor.LoadImage(m_strImagePath); 
		// 加载图像
		if (!m_imgProcessor.LoadImage(m_strImagePath))
		{
			AfxMessageBox(_T("无法打开图像文件"));
			return;
		}
		// 将图像显示在控件上
		
		// 获取图像数据
		cv::Mat image = m_imgProcessor.GetCurrentImage();

		// 将图片转换为适合显示的格式（BGR to RGB）
		cv::Mat rgbImage;
		cv::cvtColor(image, rgbImage, cv::COLOR_BGR2RGB);

		// 显示图像的代码
		CImage cimage;
		cimage.Create(rgbImage.cols, rgbImage.rows, 24);

		for (int y = 0; y < rgbImage.rows; ++y)
		{
			uchar* pSrc = rgbImage.ptr<uchar>(y);
			uchar* pDst = (uchar*)cimage.GetPixelAddress(0, y);
			memcpy(pDst, pSrc, rgbImage.cols * 3);
		}

		// 获取静态控件的矩形区域，调整图片大小
		CRect rect;
		GetDlgItem(IDC_STATIC)->GetClientRect(&rect);

		// 缩放图片以适应控件大小
		CDC* pDC = GetDC();
		HDC hDC = pDC->m_hDC;
		cimage.StretchBlt(hDC, 0, 0, rect.Width(), rect.Height(), 0, 0, rgbImage.cols, rgbImage.rows, SRCCOPY);

		// 释放设备上下文
		ReleaseDC(pDC);
	}
}

void CImageOperateDlg::OnBnClickedZoomIn()
{
	m_imgProcessor.ScaleImage(1.2);  // 放大 1.2 倍
	// 显示放大后的图像
	// ...
}

void CImageOperateDlg::OnBnClickedSaveImage()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CImageOperateDlg::OnBnClickedZoomOut()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CImageOperateDlg::OnBnClickedRotate()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CImageOperateDlg::OnBnClickedFlipH()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CImageOperateDlg::OnBnClickedFlipV()
{
	// TODO: 在此添加控件通知处理程序代码
}

