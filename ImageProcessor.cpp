#include "pch.h"
#include "ImageProcessor.h"
#include <opencv2/highgui/highgui_c.h>

ImageProcessor::ImageProcessor()
{
    cv::namedWindow("ImageWindow");
    auto _1 = (HWND)cvGetWindowHandle("ImageWindow");
    ShowWindow(_1, 0);
}

bool ImageProcessor::OpenImage(CString filePath)
{
    // 使用 OpenCV 加载图像
    CurrentImage = cv::imread(filePath.GetBuffer());
    TempImage = CurrentImage.clone();
    CurrentImage.copyTo(TempImage);
    return !CurrentImage.empty(); // 如果图像读取成功，返回 true
}

cv::Mat ImageProcessor::ScaleImage(double scaleFactor)
{
    if (!CurrentImage.empty())
    {
        cv::resize(CurrentImage, CurrentImage, cv::Size(), scaleFactor, scaleFactor);
        return CurrentImage;
    }
}

cv::Mat ImageProcessor::RotateImage(double angle)
{
    if (!CurrentImage.empty())
    {
        cv::Point2f center(CurrentImage.cols / 2.0f, CurrentImage.rows / 2.0f);
        cv::Mat rotMat = cv::getRotationMatrix2D(center, angle, 1.0);
        cv::warpAffine(CurrentImage, CurrentImage, rotMat, CurrentImage.size());
        return CurrentImage;
    }
}

cv::Mat ImageProcessor::FlipImage(bool horizontal, bool vertical)
{
    int flipCode = 0;
    if (horizontal && vertical) flipCode = -1;
    else if (horizontal) flipCode = 1;
    else if (vertical) flipCode = 0;

    cv::flip(CurrentImage, CurrentImage, flipCode);
    return CurrentImage;
}

bool ImageProcessor::SaveImage(CString filePath)
{
    return cv::imwrite(filePath.GetBuffer(), CurrentImage);
}

cv::Mat ImageProcessor::GetCurrentImage() const
{
    return CurrentImage;
}

cv::Mat ImageProcessor::GetTempImage() const
{
    return TempImage;
}

ImageProcessor::operator bool() {
    return !CurrentImage.empty();
}

HWND ImageProcessor::GetHandle() const {
    auto _1 = (HWND)cvGetWindowHandle("ImageWindow");
    return _1;
}