#pragma once
#include <opencv.hpp>


class CImageProcessor
{
public:
    CImageProcessor();
    bool LoadImage(CString filePath);  // ����ͼ��
    void ScaleImage(double scaleFactor);      // ����ͼ��
    void RotateImage(double angle);           // ��תͼ��
    void FlipImage(bool horizontal, bool vertical);  // ��תͼ��
    bool SaveImage(CString filePath);  // ����ͼ��

    cv::Mat GetCurrentImage() const;

private:
    cv::Mat m_currentImage;  // ��ǰͼ��
};

