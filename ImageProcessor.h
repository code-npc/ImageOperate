#pragma once
#include <opencv.hpp>


class CImageProcessor
{
public:
    CImageProcessor();
    bool LoadImage(const CString& filePath);  // ����ͼ��
    void ScaleImage(double scaleFactor);      // ����ͼ��
    void RotateImage(double angle);           // ��תͼ��
    void FlipImage(bool horizontal, bool vertical);  // ��תͼ��
    bool SaveImage(const CString& filePath);  // ����ͼ��

    cv::Mat GetCurrentImage() const;

private:
    cv::Mat m_currentImage;  // ��ǰͼ��
};

