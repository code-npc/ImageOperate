#include "pch.h"
#include "ImageProcessor.h"


CImageProcessor::CImageProcessor()
{
}

bool CImageProcessor::LoadImage(CString filePath)
{
    // 使用 OpenCV 加载图像
    m_currentImage = cv::imread(filePath.GetBuffer(), cv::IMREAD_COLOR);
    return !m_currentImage.empty(); // 如果图像读取成功，返回 true
}

void CImageProcessor::ScaleImage(double scaleFactor)
{
   /* if (!m_currentImage.empty())
    {
        cv::resize(m_currentImage, m_currentImage, cv::Size(), scaleFactor, scaleFactor);
    }*/
}

void CImageProcessor::RotateImage(double angle)
{
    /*if (!m_currentImage.empty())
    {
        cv::Point2f center(m_currentImage.cols / 2.0, m_currentImage.rows / 2.0);
        cv::Mat rotMat = cv::getRotationMatrix2D(center, angle, 1.0);
        cv::warpAffine(m_currentImage, m_currentImage, rotMat, m_currentImage.size());
    }*/
}

void CImageProcessor::FlipImage(bool horizontal, bool vertical)
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

bool CImageProcessor::SaveImage(CString filePath)
{
    return cv::imwrite(filePath.GetBuffer(), m_currentImage);
}

cv::Mat CImageProcessor::GetCurrentImage() const
{
    return m_currentImage;
}