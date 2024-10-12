#pragma once
#include <opencv.hpp>


class ImageProcessor
{
public:
    ImageProcessor();
    bool OpenImage(CString filePath);  // ¼ÓÔØÍ¼Ïñ
    void ScaleImage(double scaleFactor);      // Ëõ·ÅÍ¼Ïñ
    void RotateImage(double angle);           // Ðý×ªÍ¼Ïñ
    void FlipImage(bool horizontal, bool vertical);  // ·­×ªÍ¼Ïñ
    bool SaveImage(CString filePath);  // ±£´æÍ¼Ïñ



    cv::Mat GetCurrentImage() const;

    operator bool();

private:
    cv::Mat CurrentImage;  // µ±Ç°Í¼Ïñ
};

