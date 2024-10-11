#pragma once
#include <opencv.hpp>


class CImageProcessor
{
public:
    CImageProcessor();
    bool LoadImage(const CString& filePath);  // ¼ÓÔØÍ¼Ïñ
    void ScaleImage(double scaleFactor);      // Ëõ·ÅÍ¼Ïñ
    void RotateImage(double angle);           // Ðý×ªÍ¼Ïñ
    void FlipImage(bool horizontal, bool vertical);  // ·­×ªÍ¼Ïñ
    bool SaveImage(const CString& filePath);  // ±£´æÍ¼Ïñ

    cv::Mat GetCurrentImage() const;

private:
    cv::Mat m_currentImage;  // µ±Ç°Í¼Ïñ
};

