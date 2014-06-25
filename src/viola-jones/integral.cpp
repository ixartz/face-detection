//
//  integral.cpp
//  face-detection
//
//  Created by Ixi on 17/06/14.
//
//

#include "integral.h"

Integral::Integral(Camera* c)
    : Integral(c->get_camera_size())
{

}

Integral::Integral(const cv::Size& camera_size)
    : camera_size_(camera_size)
    , integral_(camera_size, CV_32SC1)
    , integral_squared_(camera_size, CV_64FC1)
{

}

void Integral::apply(cv::Mat& frame)
{
    apply(frame, integral_, integral_squared_);
}

void Integral::apply(cv::Mat& frame,
                     cv::Mat& integral,
                     cv::Mat& integral_squared)
{
    int sum = 0;
    double sum_2 = 0;

    for (int j = 0; j < frame.cols; ++j)
    {
        sum += frame.at<uchar>(0, j);
        sum_2 += frame.at<uchar>(0, j) * frame.at<uchar>(0, j);

        integral.at<int>(0, j) = sum;
        integral_squared.at<double>(0, j) = sum_2;
    }

    for (int i = 1; i < frame.rows; ++i)
    {
        sum = 0;
        sum_2 = 0;

        for (int j = 0; j < frame.cols; ++j)
        {
            sum += frame.at<uchar>(i, j);
            sum_2 += frame.at<uchar>(i, j) * frame.at<uchar>(i, j);
            integral.at<int>(i, j) = sum + integral.at<int>(i-1, j);
            integral_squared.at<double>(i, j) = sum_2 +
                                            integral_squared.at<double>(i-1, j);
        }
    }
}

cv::Mat& Integral::get_result()
{
    return integral_;
}

cv::Mat& Integral::get_result_squared()
{
    return integral_squared_;
}