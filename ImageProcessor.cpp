#include "pch.h"
#include "ImageProcessor.h"
#include <opencv2/highgui/highgui_c.h>

ImageProcessor::ImageProcessor()
{
    cv::namedWindow("OriginalImageWindow");
    auto _1 = (HWND)cvGetWindowHandle("OriginalImageWindow");
    ShowWindow(_1, 0);
    cv::namedWindow("ResultImageWindow");
    auto _2 = (HWND)cvGetWindowHandle("ResultImageWindow");
    ShowWindow(_2, 0);
}

bool ImageProcessor::OpenImage(CString filePath)
{
    // 使用 OpenCV 加载图像
    CurrentImage = cv::imread(filePath.GetBuffer());
    TempImage = TargetImage = CurrentImage;
    return !CurrentImage.empty(); // 如果图像读取成功，返回 true
}

cv::Mat ImageProcessor::ScaleImage(double scaleFactor)
{
    if (!TempImage.empty())
    {
        cv::resize(TempImage, TargetImage, cv::Size(), scaleFactor, scaleFactor);
        return TargetImage;
    }
}

cv::Mat ImageProcessor::RotateImage(double angle)
{
    if (!TempImage.empty())
    {
        cv::Point2f center(TempImage.cols / 2.0f, TempImage.rows / 2.0f);
        cv::Mat rotMat = cv::getRotationMatrix2D(center, angle, 1.0);
        cv::warpAffine(TempImage, TargetImage, rotMat, TempImage.size());
        return TargetImage;
    }
}

cv::Mat ImageProcessor::FlipImage(bool horizontal, bool vertical)
{
    int flipCode = 0;
    if (horizontal && vertical) flipCode = -1;
    else if (horizontal) flipCode = 1;
    else if (vertical) flipCode = 0;

    cv::flip(TempImage, TargetImage, flipCode);
    return TargetImage;
}

bool ImageProcessor::SaveImage(CString filePath)
{
    return cv::imwrite(filePath.GetBuffer(), TargetImage);
}

cv::Mat ImageProcessor::GetCurrentImage() const
{
    return CurrentImage;
}

cv::Mat ImageProcessor::GetTargetImage() const
{
    return TargetImage;
}

cv::Mat ImageProcessor::GetTempImage() const
{
    return TempImage;
}

ImageProcessor::operator bool() {
    return !CurrentImage.empty();
}

std::tuple<HWND,HWND> ImageProcessor::GetHandle() const {
    auto _1 = (HWND)cvGetWindowHandle("OriginalImageWindow");
    auto _2 = (HWND)cvGetWindowHandle("ResultImageWindow");
    return { _1, _2 };
}