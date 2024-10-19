#pragma once
#include <opencv.hpp>


class ImageProcessor {

    cv::Mat CurrentImage;  // ��ǰͼ��
    cv::Mat TargetImage;  // ������ͼ��
    cv::Mat TempImage;  // ��ʱ�õ�ͼ��ʵ�ֶ��ͼƬ�任

public:
    friend class CImageOperateDlg;

    ImageProcessor();
    bool OpenImage(CString filePath);  // ����ͼ��
    bool SaveImage(CString filePath);  // ����ͼ��

    cv::Mat ScaleImage(double scaleFactor);      // ����ͼ��
    cv::Mat RotateImage(double angle);           // ��תͼ��
    cv::Mat FlipImage(bool horizontal, bool vertical);  // ��תͼ��



    cv::Mat GetCurrentImage() const;
    cv::Mat GetTargetImage() const;
    cv::Mat GetTempImage() const;

    std::tuple<HWND, HWND> GetHandle() const ;

    operator bool();
    
};

