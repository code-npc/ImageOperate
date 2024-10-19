#include "pch.h"
#include "framework.h"
#include "ImageOperate.h"
#include "ImageOperateDlg.h"
#include "afxdialogex.h"

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



	auto [origin_handle, result_handle] = image_processor.GetHandle();
	HWND hParent = ::GetParent(origin_handle);
	::SetParent(origin_handle, GetDlgItem(IDC_IMAGE1)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	::ShowWindow(origin_handle, SW_SHOW);

	hParent = ::GetParent(result_handle);
	::SetParent(result_handle, GetDlgItem(IDC_IMAGE2)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	::ShowWindow(result_handle, SW_SHOW);


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
	ON_WM_PAINT()
END_MESSAGE_MAP()

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
	if (!image_processor)
		return;
	
	Display();
	
		
}

void CImageOperateDlg::Display()
{
	cv::imshow("OriginalImageWindow", image_processor.CurrentImage);
	cv::imshow("ResultImageWindow", image_processor.TargetImage);
}



void CImageOperateDlg::OnBnClickedOpenImage()
{
	// 使用 CFileDialog 打开图像
	CFileDialog dlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("图片文件 (*.jpg; *.png; *.bmp; *.webp)|*.jpg; *.png; *.bmp; *.webp||"));
	if (dlg.DoModal() == IDOK)
	{
		image_path = dlg.GetPathName();
		// 加载图像
		if (!image_processor.OpenImage(image_path))
		{
			AfxMessageBox(_T("无法打开图像文件"));
			return;
		}
		Display();
	}
}

void CImageOperateDlg::OnBnClickedSaveImage()
{
	// TODO: 保存图片
	CFileDialog dlg(FALSE, _T(".jpg"), NULL, OFN_OVERWRITEPROMPT, _T("JPEG 文件 (*.jpg)|*.jpg|PNG 文件 (*.png)|*.png|所有文件 (*.*)|*.*||"));

	if (dlg.DoModal() == IDOK)
	{
		CString filePath = dlg.GetPathName();
		if (!image_processor.SaveImage(filePath.GetString()))
		{
			AfxMessageBox(_T("保存图片失败"));
		}
		else
		{
			AfxMessageBox(_T("图片保存成功"));
		}
	}
}

void CImageOperateDlg::OnBnClickedZoomIn()
{
	cv::Mat zoomedImage = image_processor.ScaleImage(1.2);  // 放大 1.2 倍
	// 显示放大后的图像
	image_processor.TargetImage = zoomedImage;
	image_processor.TempImage = image_processor.TargetImage;
	Display();
	
}

void CImageOperateDlg::OnBnClickedZoomOut()
{
	// TODO: 缩小图片
	cv::Mat zoomedImage = image_processor.ScaleImage(0.8);
	image_processor.TargetImage = zoomedImage;
	image_processor.TempImage = image_processor.TargetImage;
	Display();

}

void CImageOperateDlg::OnBnClickedRotate()
{
	// TODO: 旋转图片
	cv::Mat rotatedImage = image_processor.RotateImage(45);
	image_processor.TargetImage = rotatedImage;
	image_processor.TempImage = image_processor.TargetImage;
	Display();
}

void CImageOperateDlg::OnBnClickedFlipH()
{
	// TODO: 水平反转图像
	cv::Mat flippedImage = image_processor.FlipImage(true, false);
	image_processor.TargetImage = flippedImage;
	image_processor.TempImage = image_processor.TargetImage;
	Display();
}

void CImageOperateDlg::OnBnClickedFlipV()
{
	// TODO: 垂直反转图像
	cv::Mat flippedImage = image_processor.FlipImage(false, true);
	image_processor.TargetImage = flippedImage;
	image_processor.TempImage = image_processor.TargetImage;
	Display();
}


