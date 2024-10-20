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
	DDX_Control(pDX, IDC_IMAGE, PIC_CONTROL);
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


	auto image_handle = image_processor.GetHandle();
	HWND hParent = ::GetParent(image_handle);
	::SetParent(image_handle, GetDlgItem(IDC_IMAGE)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);
	::ShowWindow(image_handle, SW_SHOW);

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
	ON_BN_CLICKED(IDC_RESET, &CImageOperateDlg::OnBnClickedReset)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_TOGRAY, &CImageOperateDlg::OnBnClickedTogray)
	ON_BN_CLICKED(IDC_SHARPEN, &CImageOperateDlg::OnBnClickedSharpen)
	ON_BN_CLICKED(IDC_MOPI, &CImageOperateDlg::OnBnClickedMopi)
	ON_BN_CLICKED(IDC_CONTRAST, &CImageOperateDlg::OnBnClickedContrast)
	ON_BN_CLICKED(IDC_BRIGHTNESS, &CImageOperateDlg::OnBnClickedBrightness)
	ON_BN_CLICKED(IDC_BLUR, &CImageOperateDlg::OnBnClickedBlur)
	ON_BN_CLICKED(IDC_OPEN_CAMERA, &CImageOperateDlg::OnBnClickedOpenCamera)
	ON_BN_CLICKED(IDC_TAKE_PICTURE, &CImageOperateDlg::OnBnClickedTakePicture)
	ON_BN_CLICKED(IDC_RECORD_VIDEO, &CImageOperateDlg::OnBnClickedRecordVideo)
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
	setPictureColorBGR();
	cv::imshow("ImageWindow", image_processor.CurrentImage);

}

void CImageOperateDlg::setPictureColorBGR()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rc;
	CWnd* pWnd = GetDlgItem(IDC_IMAGE);
	pWnd->GetClientRect(&rc);
	int py = rc.Height();
	int px = rc.Width();

	FillRect(PIC_CONTROL.GetDC()->GetSafeHdc(), &rc, CBrush(RGB(255, 255, 255)));

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
	image_processor.ScaleImage(1.2);  // 放大 1.2 倍
	// 显示放大后的图像
	Display();
	
}

void CImageOperateDlg::OnBnClickedZoomOut()
{
	// TODO: 缩小图片
	image_processor.ScaleImage(0.8);
	Display();
}

void CImageOperateDlg::OnBnClickedRotate()
{
	image_processor.RotateImage(45);
	Display();
}

void CImageOperateDlg::OnBnClickedFlipH()
{
	// TODO: 水平反转图像
	image_processor.FlipImage(true, false);
	Display();
}

void CImageOperateDlg::OnBnClickedFlipV()
{
	// TODO: 垂直反转图像
	image_processor.FlipImage(false, true);
	Display();
}

void CImageOperateDlg::OnBnClickedReset()
{
	image_processor.CurrentImage = image_processor.TempImage.clone();
	image_processor.TempImage.copyTo(image_processor.CurrentImage);
	Display();
}

void CImageOperateDlg::OnBnClickedTogray()
{
	cv::cvtColor(image_processor.CurrentImage, image_processor.CurrentImage, cv::COLOR_BGR2GRAY);
	Display();
}


void CImageOperateDlg::OnBnClickedSharpen()
{
	// TODO: 在此添加控件通知处理程序代码
	char arith[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };       //使用拉普拉斯算子
	int rows = image_processor.CurrentImage.rows;        //原图的行
	int cols = image_processor.CurrentImage.cols * image_processor.CurrentImage.channels();   //原图的列
	int offsetx = image_processor.CurrentImage.channels();       //像素点的偏移量


	for (int i = 1; i < rows - 1; i++)
	{
		const uchar* previous = image_processor.CurrentImage.ptr<uchar>(i - 1);
		const uchar* current = image_processor.CurrentImage.ptr<uchar>(i);
		const uchar* next = image_processor.CurrentImage.ptr<uchar>(i + 1);
		uchar* output = image_processor.CurrentImage.ptr<uchar>(i - 1);
		for (int j = offsetx; j < cols - offsetx; j++)
		{
			output[j - offsetx] =
				cv::saturate_cast<uchar>(previous[j - offsetx] * arith[0] + previous[j] * arith[1] + previous[j + offsetx] * arith[2] +
					current[j - offsetx] * arith[3] + current[j] * arith[4] + current[j + offsetx] * arith[5] +
					next[j - offsetx] * arith[6] + next[j] * arith[7] + next[j - offsetx] * arith[8]);
		}
	}
	Display();
}


void CImageOperateDlg::OnBnClickedMopi()
{
	// 融合原图与模糊图，这里以0.5的比例融合
	auto alpha = 0.8;
	cv::GaussianBlur(image_processor.CurrentImage, image_processor.CurrentImage,cv::Size(21, 21), 0);
	cv::addWeighted(image_processor.TempImage, alpha, image_processor.CurrentImage, 1 - alpha, 0, image_processor.CurrentImage);
	Display();
}


void CImageOperateDlg::OnBnClickedContrast()
{
	// 灰度图增强对比度
	cv::equalizeHist(image_processor.CurrentImage, image_processor.CurrentImage);
	Display();
}


void CImageOperateDlg::OnBnClickedBrightness()
{
	image_processor.CurrentImage.convertTo(image_processor.CurrentImage, -1, 1.2, 50);
	Display();
}


void CImageOperateDlg::OnBnClickedBlur()
{
	cv::GaussianBlur(image_processor.CurrentImage, image_processor.CurrentImage, cv::Size(5, 5), 0, 0);
	Display();
}


void CImageOperateDlg::OnBnClickedOpenCamera()
{
	cv::VideoCapture cap(0);
	while (1)
	{
		cv::Mat camera;
		cap >> camera;//获取当前帧图像
		cv::imshow("CAMREA_WINDOW", camera);//显示当前帧图像
		cv::waitKey(8);//延时30秒
	}
}


void CImageOperateDlg::OnBnClickedTakePicture()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CImageOperateDlg::OnBnClickedRecordVideo()
{
	// TODO: 在此添加控件通知处理程序代码
}
