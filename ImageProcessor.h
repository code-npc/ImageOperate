#pragma once
#include <opencv.hpp>


class ImageProcessor {

    cv::Mat CurrentImage;  // 当前图像
    cv::Mat TempImage;  // 用来记录原图

public:
    friend class CImageOperateDlg;

    ImageProcessor();
    bool OpenImage(CString filePath);  // 加载图像
    bool SaveImage(CString filePath);  // 保存图像

    cv::Mat ScaleImage(double scaleFactor);      // 缩放图像
    cv::Mat RotateImage(double angle);           // 旋转图像
    cv::Mat FlipImage(bool horizontal, bool vertical);  // 翻转图像



    cv::Mat GetCurrentImage() const;
    cv::Mat GetTempImage() const;

    HWND GetHandle() const ;

    operator bool();
    
};

