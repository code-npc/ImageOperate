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
public:

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

	OperateMenu.LoadMenu(IDR_MENU);
	SetMenu(&OperateMenu);

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
	ON_BN_CLICKED(ID_OPEN_FILE, &CImageOperateDlg::OnBnClickedOpenImage)
	ON_BN_CLICKED(ID_SAVE_FILE, &CImageOperateDlg::OnBnClickedSaveImage)
	ON_BN_CLICKED(ID_ZOOM_IN, &CImageOperateDlg::OnBnClickedZoomIn)
	ON_BN_CLICKED(ID_ZOOM_OUT, &CImageOperateDlg::OnBnClickedZoomOut)
	ON_BN_CLICKED(ID_ROTATE, &CImageOperateDlg::OnBnClickedRotate)
	ON_BN_CLICKED(ID_FLIP_Y, &CImageOperateDlg::OnBnClickedFlipY)
	ON_BN_CLICKED(ID_FLIP_X, &CImageOperateDlg::OnBnClickedFlipX)
	ON_BN_CLICKED(ID_RESET, &CImageOperateDlg::OnBnClickedReset)
	ON_WM_PAINT()
	ON_BN_CLICKED(ID_TO_GRAY, &CImageOperateDlg::OnBnClickedTogray)
	ON_BN_CLICKED(ID_SHARPEN, &CImageOperateDlg::OnBnClickedSharpen)
	ON_BN_CLICKED(ID_MOPI, &CImageOperateDlg::OnBnClickedMopi)
	ON_BN_CLICKED(ID_CONTRAST, &CImageOperateDlg::OnBnClickedContrast)
	ON_BN_CLICKED(ID_BRIGHTNESS, &CImageOperateDlg::OnBnClickedBrightness)
	ON_BN_CLICKED(ID_SATUATION, &CImageOperateDlg::OnBnClickedSatuation)
	ON_BN_CLICKED(ID_GAUSS_BLUR, &CImageOperateDlg::OnBnClickedBlur)
	ON_BN_CLICKED(ID_OPEN_CAMERA, &CImageOperateDlg::OnBnClickedOpenCamera)
	ON_BN_CLICKED(ID_TAKE_PHOTO, &CImageOperateDlg::OnBnClickedTakePicture)
	ON_BN_CLICKED(ID_START_VIDEO, &CImageOperateDlg::OnBnClickedRecordVideo)
	ON_BN_CLICKED(ID_CLOSE_CAMERA, &CImageOperateDlg::OnBnClickedCloseCamrea)
	ON_BN_CLICKED(ID_END_VIDEO, &CImageOperateDlg::OnBnClickedRecordOver)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_Brightness, &CImageOperateDlg::OnNMCustomdrawSliderBrightness)

	ON_BN_CLICKED(ID_keyboards, &CImageOperateDlg::Onkeyboards)
	ON_BN_CLICKED(ID_colorMap, &CImageOperateDlg::Oncolormap)
	ON_BN_CLICKED(ID_channels, &CImageOperateDlg::Onchannels)
	ON_BN_CLICKED(ID_colorRange, &CImageOperateDlg::Onrange)
	ON_BN_CLICKED(ID_simpledraw, &CImageOperateDlg::Onsimpledraw)
	ON_BN_CLICKED(ID_poly, &CImageOperateDlg::Onpoly)
	ON_BN_CLICKED(ID_MOUSE_DRAW, &CImageOperateDlg::OnMouseDraw)
	ON_BN_CLICKED(ID_NORMAL, &CImageOperateDlg::OnNormalization)
	ON_BN_CLICKED(ID_DRAW_HIST, &CImageOperateDlg::OnDrawHist)
	ON_BN_CLICKED(ID_FACE_DETECTOR, &CImageOperateDlg::OnFaceDetector)
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
	Display();
	
}

void CImageOperateDlg::OnBnClickedZoomOut()
{
	image_processor.ScaleImage(0.8);
	Display();
}

void CImageOperateDlg::OnBnClickedRotate()
{
	image_processor.RotateImage(45);
	Display();
}

void CImageOperateDlg::OnBnClickedFlipY()
{
	image_processor.FlipImage(true, false);
	Display();
}

void CImageOperateDlg::OnBnClickedFlipX()
{
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
	image_processor.CurrentImage = image_processor.MopiImage();
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

void CImageOperateDlg::OnBnClickedSatuation()
{
	image_processor.SatuationImage(1.3);
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
		cap.read(image_processor.CurrentImage);
		Display(1);
		//OnBnClickedTogray();
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
	image_processor.BrightnessImage(val);
	Display();
}


//Demo实现
void CImageOperateDlg::Onkeyboards()
{
	cv::imshow("输出窗口", image_processor.CurrentImage);
	int key = cv::waitKey(0);
	while (true) {
		int key = cv::waitKey(1000);
		if (key == 49) {
			image_processor.ToGrayImage();
			cv::imshow("输出窗口", image_processor.CurrentImage);
		}
		if (key == 50) {
			image_processor.BlurImage();
			cv::imshow("输出窗口", image_processor.CurrentImage);
		}
		if (key == 27) {
			break;
		}
		
	}
	CString strMessage;
	strMessage.Format(_T("这是一条格式化的消息框输出：%d"), key);
	AfxMessageBox(strMessage);
}

void CImageOperateDlg::Oncolormap()
{
	int colormap[] = {
	cv::COLORMAP_AUTUMN,
	cv::COLORMAP_BONE,
	cv::COLORMAP_JET,
	cv::COLORMAP_WINTER,
	cv::COLORMAP_RAINBOW,
	cv::COLORMAP_OCEAN,
	cv::COLORMAP_SUMMER,
	cv::COLORMAP_SPRING,
	cv::COLORMAP_COOL,
	cv::COLORMAP_HSV,
	cv::COLORMAP_PINK,
	cv::COLORMAP_HOT,
	cv::COLORMAP_PARULA,
	cv::COLORMAP_MAGMA,
	cv::COLORMAP_INFERNO,
	cv::COLORMAP_PLASMA,
	cv::COLORMAP_VIRIDIS,
	cv::COLORMAP_CIVIDIS,
	cv::COLORMAP_TWILIGHT,
	cv::COLORMAP_TWILIGHT_SHIFTED
	};
	int index = 2;
	cv::applyColorMap(image_processor.TempImage, image_processor.CurrentImage, colormap[index]);
	Display();
}

void CImageOperateDlg::Onchannels()
{
	cv::Mat image = image_processor.CurrentImage;
	std::vector<cv::Mat> vec;
	cv::split(image_processor.CurrentImage, vec);
	//cv::imshow("通道1", vec[0]);
	//cv::imshow("通道2", vec[1]);
	//cv::imshow("通道3", vec[2]);

	vec[0] = 0;
	vec[1] = 0;
	cv::merge(vec, image);
	Display();
}

void CImageOperateDlg::Onrange()
{
	cv::Mat hsv;
	cv::Mat mask;
	cv::Mat image = image_processor.CurrentImage;
	cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
	cv::inRange(hsv, cv::Scalar(35, 43, 46), cv::Scalar(77, 255, 255), mask);
	//cv::imshow("色彩空间转换", mask);
	cv::Mat redback = cv::Mat::zeros(image.size(), image.type());
	redback = cv::Scalar(40, 40, 200);
	//cv::imshow("红色背景", redback);
	cv::bitwise_not(mask, mask);
	image.copyTo(redback, mask);
	redback.copyTo(image);
	Display();
}

void CImageOperateDlg::Onsimpledraw()
{
	cv::Mat image = image_processor.CurrentImage;

	cv::Rect rect(100,100,300,300);
	cv::rectangle(image, rect, cv::Scalar(255, 0, 0), 2);

	cv::circle(image, cv::Point(200, 200), 40, cv::Scalar(0, 255, 0), 2);
	cv::line(image, cv::Point(200, 200), cv::Point(500, 500), cv::Scalar(0, 0, 255), 2);
	
	cv::RotatedRect rrt;
	rrt.center = cv::Point(300, 400);
	rrt.size = cv::Size(100, 200);
	rrt.angle = 90;
	cv::ellipse(image, rrt, cv::Scalar(183, 42, 90), 2);
	Display();
}

void CImageOperateDlg::Onpoly()
{
	cv::Mat image = image_processor.CurrentImage;
	std::vector<cv::Point> points;
	points.push_back(cv::Point(100,100));
	points.push_back(cv::Point(350,100));
	points.push_back(cv::Point(450,280));
	points.push_back(cv::Point(320,450));
	points.push_back(cv::Point(80,400));
	cv::polylines(image, points, true, cv::Scalar(0, 255, 0), 2);
	cv::fillPoly(image, points, cv::Scalar(255, 0, 0));

	/*std::vector<std::vector<cv::Point>> contours;
	contours.push_back(points);
	cv::drawContours(image, contours, 0, cv::Scalar(255, 0, 0), -1);*/
	Display();
}

void CImageOperateDlg::OnMouseDraw()
{
	image_processor.MouseDraw();
	Display();
}

void CImageOperateDlg::OnNormalization()
{
	image_processor.NormalImage();
	Display();
}

void CImageOperateDlg::OnDrawHist()
{
	image_processor.DrawHist();
	Display();
}

void CImageOperateDlg::OnFaceDetector()
{
	using namespace cv;
	using namespace std;
	//文件夹路径
	string root_dir = "D:/Develop/Libs/opencv/sources/samples/dnn/face_detector/";

	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");

	//对摄像头进行人脸检测
	VideoCapture cap(0);
	Mat frame;
	while (true) {

		cap.read(frame);//frame为输出，read是将捕获到的视频一帧一帧的传入frame

		if (frame.empty()) {
			break;
		}

		//准备深度学习模型需要的数据 （blob-斑点）
		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
		net.setInput(blob);

		//完成推理
		Mat probs = net.forward();

		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());

		//解析结果
		for (int i = 0; i < detectionMat.rows; i++) {

			float confidence = detectionMat.at<float>(i, 2);//第三个值 得分

			if (confidence > 0.6) {

				//因为预测来的值为[0,1]范围的数，我们还需要*原图像的宽度和长度
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

				Rect rect(x1, y1, x2 - x1, y2 - y1);
				rectangle(frame, rect, Scalar(0, 0, 255), 2, 8, 0);
			}
		}

		imshow("ImageWindow", frame);

		int c = waitKey(1);
		if (c == 27) {
			break;
		}
	}
	cap.release();
}
