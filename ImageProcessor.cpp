#include "pch.h"
#include "ImageProcessor.h"
#include <opencv2/highgui/highgui_c.h>

ImageProcessor::ImageProcessor()
{
    cv::namedWindow("ImageWindow");
    cv::resizeWindow("ImageWindow", 0, 0);
    auto _1 = (HWND)cvGetWindowHandle("ImageWindow");
    ShowWindow(_1, 0);
}

bool ImageProcessor::OpenImage(CString filePath)
{
    // 使用 OpenCV 加载图像
    CurrentImage = cv::imread(filePath.GetBuffer());
    TempImage = CurrentImage.clone();
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

cv::Mat ImageProcessor::ToGrayImage()
{
    cv::cvtColor(CurrentImage, CurrentImage, cv::COLOR_BGR2GRAY);
    return CurrentImage;
}

cv::Mat ImageProcessor::SharpenImage()
{
    char arith[9] = { 0, -1, 0, -1, 5, -1, 0, -1, 0 };       //使用拉普拉斯算子
    int rows = CurrentImage.rows;        //原图的行
    int cols = CurrentImage.cols * CurrentImage.channels();   //原图的列
    int offsetx = CurrentImage.channels();       //像素点的偏移量

    for (int i = 1; i < rows - 1; i++)
    {
        const uchar* previous = CurrentImage.ptr<uchar>(i - 1);
        const uchar* current = CurrentImage.ptr<uchar>(i);
        const uchar* next = CurrentImage.ptr<uchar>(i + 1);
        uchar* output = CurrentImage.ptr<uchar>(i - 1);
        for (int j = offsetx; j < cols - offsetx; j++)
        {
            output[j - offsetx] =
                cv::saturate_cast<uchar>(previous[j - offsetx] * arith[0] + previous[j] * arith[1] + previous[j + offsetx] * arith[2] +
                    current[j - offsetx] * arith[3] + current[j] * arith[4] + current[j + offsetx] * arith[5] +
                    next[j - offsetx] * arith[6] + next[j] * arith[7] + next[j - offsetx] * arith[8]);
        }
    }
    return CurrentImage;
}

cv::Mat ImageProcessor::MopiImage()
{
    cv::GaussianBlur(CurrentImage, CurrentImage, cv::Size(21, 21), 0);
    return CurrentImage;
}

cv::Mat ImageProcessor::ContrastImage()
{
    cv::equalizeHist(CurrentImage, CurrentImage);
    return CurrentImage;
}

cv::Mat ImageProcessor::BrightnessImage(int val)
{
    //CurrentImage.convertTo(CurrentImage, -1, 1.2, 50);
    
    cv::add(CurrentImage, cv::Scalar(val, val, val), CurrentImage);
    return CurrentImage;
}

cv::Mat ImageProcessor::BlurImage()
{
    cv::GaussianBlur(CurrentImage, CurrentImage, cv::Size(5, 5), 0, 0);
    return CurrentImage;
}

static void on_lightness(int b, void* userdata) {
    cv::Mat image = *((cv::Mat*)userdata);
    cv::Mat dst = cv::Mat::zeros(image.size(), image.type());
    cv::Mat m = cv::Mat::zeros(image.size(), image.type());
    cv::addWeighted(image, 1.0, m, 0, b, dst);
    cv::imshow("亮度", dst);
}

static void on_contrast(int b, void* userdata) {
    cv::Mat image = *((cv::Mat*)userdata);
    cv::Mat dst = cv::Mat::zeros(image.size(), image.type());
    cv::Mat m = cv::Mat::zeros(image.size(), image.type());
    double contrast = b / 100.0;
    cv::addWeighted(image, contrast, m, 0.0, 0, dst);
    //展示
    cv::imshow("亮度", dst);
}

void ImageProcessor::TrackBar(cv::Mat &CurrentImage)
{
    int lightness = 50;
    int max_value = 100;
    int contrast_value = 100;
    cv::createTrackbar("亮度：", "ImageWindow", &lightness, max_value, on_lightness, (void*)(&CurrentImage));
    cv::createTrackbar("亮度：", "ImageWindow", &contrast_value, 200, on_contrast, (void*)(&CurrentImage));
    on_lightness(50, &CurrentImage);
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