#include "pch.h"
#include "ImageProcessor.h"


ImageProcessor::ImageProcessor()
{
}

bool ImageProcessor::OpenImage(CString filePath)
{
    // 使用 OpenCV 加载图像
    CurrentImage = cv::imread(filePath.GetBuffer());
    return !CurrentImage.empty(); // 如果图像读取成功，返回 true
}

void ImageProcessor::ScaleImage(double scaleFactor)
{
   /* if (!m_currentImage.empty())
    {
        cv::resize(m_currentImage, m_currentImage, cv::Size(), scaleFactor, scaleFactor);
    }*/
}

void ImageProcessor::RotateImage(double angle)
{
    /*if (!m_currentImage.empty())
    {
        cv::Point2f center(m_currentImage.cols / 2.0, m_currentImage.rows / 2.0);
        cv::Mat rotMat = cv::getRotationMatrix2D(center, angle, 1.0);
        cv::warpAffine(m_currentImage, m_currentImage, rotMat, m_currentImage.size());
    }*/
}

void ImageProcessor::FlipImage(bool horizontal, bool vertical)
{
  /*  int flipCode = 0;
    if (horizontal && vertical)
        flipCode = -1;
    else if (horizontal)
        flipCode = 1;
    else if (vertical)
        flipCode = 0;

    cv::flip(m_currentImage, m_currentImage, flipCode);*/
}

bool ImageProcessor::SaveImage(CString filePath)
{
    return cv::imwrite(filePath.GetBuffer(), CurrentImage);
}

cv::Mat ImageProcessor::GetCurrentImage() const
{
    return CurrentImage;
}

ImageProcessor::operator bool() {
    return !CurrentImage.empty();
}
