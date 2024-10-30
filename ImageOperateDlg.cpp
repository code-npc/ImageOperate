﻿#include "pch.h"
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
	DDX_Control(pDX, IDC_SLIDER_Brightness, BrightnessSlider);
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
	//CDialogEx::OnInitDialog();
	BrightnessSlider.SetRange(-10, 25);//设置滑动范围
	BrightnessSlider.SetTicFreq(1);//每1个单位画一刻度
	BrightnessSlider.SetPos(0);//设置滑块初始位置
	

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
	ON_BN_CLICKED(IDC_CLOSE_CAMREA, &CImageOperateDlg::OnBnClickedCloseCamrea)
	ON_BN_CLICKED(IDC_RECORD_OVER, &CImageOperateDlg::OnBnClickedRecordOver)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Brightness, &CImageOperateDlg::OnNMCustomdrawSliderBrightness)
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

void CImageOperateDlg::Display(bool flag)
{
	cv::imshow("ImageWindow", image_processor.CurrentImage);
}

void CImageOperateDlg::setPictureColorBGR()
{
	CPaintDC dc(this);
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
	Display();
}

void CImageOperateDlg::OnBnClickedTogray()
{
	image_processor.ToGrayImage();
	Display();
}

void CImageOperateDlg::OnBnClickedSharpen()
{
	image_processor.SharpenImage();
	Display();
}

void CImageOperateDlg::OnBnClickedMopi()
{
	image_processor.MopiImage();
	Display();
}

void CImageOperateDlg::OnBnClickedContrast()
{
	// 灰度图增强对比度
	image_processor.ContrastImage();
	Display();
}

void CImageOperateDlg::OnBnClickedBrightness()
{
	image_processor.BrightnessImage(10);
	Display();
}

void CImageOperateDlg::OnBnClickedBlur()
{
	image_processor.BlurImage();
	Display();
}

void CImageOperateDlg::OnBnClickedOpenCamera()
{
	closeFlag = false;
	cv::VideoCapture cap(0);
	setPictureColorBGR();
	while (1){
		cap >> image_processor.CurrentImage;//获取当前帧图像
		Display(1);
		if (takePhotoFlag){
			takePhotoFlag = false;
			//生成并转换照片名称
			auto m_time = CTime::GetCurrentTime();
			CString m_strDateTime = path + m_time.Format(_T("%Y%m%d%H%M%S.jpg"));
			std::string name = (m_strDateTime.GetBuffer());
			//将Mat数据写入文件
			bool res = cv::imwrite(name, image_processor.CurrentImage);
		}
		if (closeFlag) break;  // 结束监控
		
		cv::waitKey(30);
	}
}

void CImageOperateDlg::OnBnClickedTakePicture()
{
	takePhotoFlag = true;
}

void CImageOperateDlg::OnBnClickedRecordVideo()
{
	//开启摄像头
	cv::VideoCapture capture(0);
	// 获取视频参数
	int width = capture.get(cv::CAP_PROP_FRAME_WIDTH);
	int height = capture.get(cv::CAP_PROP_FRAME_HEIGHT);
	int count = capture.get(cv::CAP_PROP_FRAME_COUNT);
	double fps = capture.get(cv::CAP_PROP_FPS);

	//生成录制文件名
	CTime m_time;
	m_time = CTime::GetCurrentTime();
	CString videoNameCString = path + m_time.Format(_T("%Y%m%d%H%M%S.avi")); //格式化日期时间
	std::string videoName = (videoNameCString.GetBuffer());

	//实例化VideoWriter对象
	cv::VideoWriter writer(videoName, cv::VideoWriter::fourcc('D', 'I', 'V', 'X'), 30, cv::Size(width, height), true);

	//生成实时监控名
	cv::Mat frame;

	//循环播放并录制
	while (true) {
		//读帧数据，显示数据
		capture.read(frame);
		flip(frame, frame, 1);
		if (frame.empty()) break;
		//帧写入视频文件
		writer.write(frame);
		cv::waitKey(30);
		if (recordFlag) break;
	}

	//重置录制状态
	recordFlag = false;
	//释放写视频对象
	writer.release();
}

void CImageOperateDlg::OnBnClickedCloseCamrea()
{
	closeFlag = true;
	setPictureColorBGR();
}

void CImageOperateDlg::OnBnClickedRecordOver()
{
	recordFlag = true;
	setPictureColorBGR();
}

//滑动，调节亮度
void CImageOperateDlg::OnNMCustomdrawSliderBrightness(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;

	if (!image_processor)
		return;
	int val = BrightnessSlider.GetPos();
	/*cv::Mat m = cv::Mat::zeros(image_processor.CurrentImage.size(), image_processor.CurrentImage.type());
	m = cv::Scalar(val, val, val);
	cv::add(image_processor.CurrentImage, cv::Scalar(val, val, val), image_processor.CurrentImage);*/
	image_processor.BrightnessImage(val);
	Display();
}
