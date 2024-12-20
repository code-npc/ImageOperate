#pragma once
#include <opencv.hpp>


class ImageProcessor {

    cv::Mat CurrentImage;  // ��ǰͼ��
    cv::Mat TempImage;  // ������¼ԭͼ
   
public:
    friend class CImageOperateDlg;

    ImageProcessor();
    bool OpenImage(CString filePath);  // ����ͼ��
    bool SaveImage(CString filePath);  // ����ͼ��

    cv::Mat ScaleImage(double scaleFactor);      // ����ͼ��
    cv::Mat RotateImage(double angle);           // ��תͼ��
    cv::Mat FlipImage(bool horizontal, bool vertical);  // ��תͼ��
    cv::Mat ToGrayImage();
    cv::Mat SharpenImage();
    cv::Mat MopiImage();
    cv::Mat ContrastImage();
    cv::Mat BrightnessImage(int val);
    cv::Mat SatuationImage(double val);
    cv::Mat BlurImage();

    static void on_Mouse(int event, int x, int y, int flag, void* userdata);
    void MouseDraw();
    void NormalImage();
    void DrawHist();
    cv::Mat GetCurrentImage() const;
    cv::Mat GetTempImage() const;

    HWND GetHandle() const ;

    operator bool();

};

