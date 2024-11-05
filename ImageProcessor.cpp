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
        /*double cos = abs(rotMat.at<double>(0, 0));
        double sin = abs(rotMat.at<double>(0, 1));
        int nw = cos * CurrentImage.cols + sin * CurrentImage.rows;
        int nh = sin * CurrentImage.cols + cos * CurrentImage.rows;
        rotMat.at<double>(0, 2) += (nw / 2 - CurrentImage.cols / 2);
        rotMat.at<double>(1, 2) += (nh / 2 - CurrentImage.rows / 2);*/
        cv::warpAffine(CurrentImage, CurrentImage, rotMat, CurrentImage.size());
        return CurrentImage;
    }
}

cv::Mat ImageProcessor::FlipImage(bool horizontal, bool vertical)
{
    if (!CurrentImage.empty()) {
        int flipCode = 0;
        if (horizontal && vertical) flipCode = -1;
        else if (horizontal) flipCode = 1;
        else if (vertical) flipCode = 0;

        cv::flip(CurrentImage, CurrentImage, flipCode);
        return CurrentImage;
    }
}

cv::Mat ImageProcessor::ToGrayImage()
{
    if (!CurrentImage.empty()) {
        cv::cvtColor(CurrentImage, CurrentImage, cv::COLOR_BGR2GRAY);
        return CurrentImage;
    }
}

cv::Mat ImageProcessor::SharpenImage()
{
    if(!CurrentImage.empty()){
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
}

cv::Mat ImageProcessor::MopiImage()
{
    if (!CurrentImage.empty()) {
        cv::GaussianBlur(CurrentImage, CurrentImage, cv::Size(21, 21), 0);
        return CurrentImage;
    }
}

cv::Mat ImageProcessor::ContrastImage()
{
    if (!CurrentImage.empty()) {
        cv::convertScaleAbs(CurrentImage, CurrentImage, 1.2, 1);
        //cv::equalizeHist(CurrentImage, CurrentImage);
        return CurrentImage;
    }
}

cv::Mat ImageProcessor::BrightnessImage(int val)
{
    if (!CurrentImage.empty()) {
        //CurrentImage.convertTo(CurrentImage, -1, 1.2, 50);

        cv::add(CurrentImage, cv::Scalar(val, val, val), CurrentImage);
        return CurrentImage;
    }
}

cv::Mat ImageProcessor::SatuationImage(double val)
{   
    if (!CurrentImage.empty()) {
        cv::cvtColor(CurrentImage, CurrentImage,cv::COLOR_BGR2HSV);

        std::vector<cv::Mat> hsvChannels;
        cv::split(CurrentImage, hsvChannels);
        hsvChannels[1].convertTo(hsvChannels[1], -1, val, 0);
        cv::merge(hsvChannels, CurrentImage);
        cv::cvtColor(CurrentImage, CurrentImage, cv::COLOR_HSV2BGR);
        return CurrentImage;
    }
}

cv::Mat ImageProcessor::BlurImage()
{
    if (!CurrentImage.empty()) {
        cv::GaussianBlur(CurrentImage, CurrentImage, cv::Size(5, 5), 0, 0);
        return CurrentImage;
    }
}

cv::Point ps(-1,-1); cv::Mat tem; cv::Point pe(-1,-1);
void ImageProcessor::on_Mouse(int event, int x, int y, int flag, void* userdata)
{
    cv::Mat image = *((cv::Mat*)userdata);
    if (event == cv::EVENT_LBUTTONDOWN) {
        ps.x = x;
        ps.y = y;
    }
    else if (event == cv::EVENT_LBUTTONUP) {
        pe.x = x;
        pe.y = y;
        int width = abs(pe.x - ps.x);
        int height = abs(pe.y - ps.y);
        if (pe.x - ps.x < 0) { std::swap(pe.x,ps.x); }
        if (pe.y - ps.y < 0) { std::swap(pe.y, ps.y); }
        cv::Rect rect(ps.x, ps.y, width, height);
        cv::rectangle(image, rect, cv::Scalar(0, 0, 255), 2);
        //cv::imshow("ROI", image(rect));
        ps.x = -1; ps.y = -1;
        cv::imshow("鼠标绘制", image);
    }
    else if (event == cv::EVENT_MOUSEMOVE) {
        if (ps.x > 0 && ps.y > 0) {
            pe.x = x;
            pe.y = y; 
            int width = abs(pe.x - ps.x);
            int height = abs(pe.y - ps.y);
            if (pe.x - ps.x < 0) { std::swap(pe.x, ps.x); }
            if (pe.y - ps.y < 0) { std::swap(pe.y, ps.y); }
            cv::Rect rect(ps.x, ps.y, width, height);
            tem.copyTo(image);
            cv::rectangle(image, rect, cv::Scalar(0, 0, 255), 2);
            cv::imshow("鼠标绘制", image);
        }
    }
}
void ImageProcessor::MouseDraw()
{
    if (!CurrentImage.empty()) {
        cv::namedWindow("鼠标绘制");
        cv::setMouseCallback("鼠标绘制", on_Mouse, (void*)(&CurrentImage));
        cv::imshow("鼠标绘制", CurrentImage);
        TempImage.copyTo(tem);
    }
}

void ImageProcessor::NormalImage()
{
    if (!CurrentImage.empty()) {
        //图像像素类型转换
        CurrentImage.convertTo(CurrentImage, CV_32F);
        //CurrentImage.convertTo(CurrentImage, CV_32F,1/255.0);
        //归一化
        cv::normalize(CurrentImage, CurrentImage, 1.0, 0, cv::NORM_MINMAX);
    }
}

bool ImageProcessor::SaveImage(CString filePath)
{
    if (!CurrentImage.empty()) {
        return cv::imwrite(filePath.GetBuffer(), CurrentImage);
    }
}



cv::Mat ImageProcessor::GetCurrentImage() const
{
    if (!CurrentImage.empty()) {
        return CurrentImage;
    }
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
 