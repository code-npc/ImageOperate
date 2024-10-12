#pragma once
#include <opencv.hpp>


class ImageProcessor
{
public:
    ImageProcessor();
    bool OpenImage(CString filePath);  // ����ͼ��
    void ScaleImage(double scaleFactor);      // ����ͼ��
    void RotateImage(double angle);           // ��תͼ��
    void FlipImage(bool horizontal, bool vertical);  // ��תͼ��
    bool SaveImage(CString filePath);  // ����ͼ��



    cv::Mat GetCurrentImage() const;

    operator bool();

private:
    cv::Mat CurrentImage;  // ��ǰͼ��
};

