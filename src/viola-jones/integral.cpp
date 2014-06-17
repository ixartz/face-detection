//
//  integral.cpp
//  face-detection
//
//  Created by Ixi on 17/06/14.
//
//

#include "integral.h"

Integral::Integral(Camera* c)
    : c_(c)
    , integral_(c->get_camera_size(), CV_32SC1)
{

}

void Integral::apply(cv::Mat& frame)
{
    int sum = 0;

    for (int j = 0; j < frame.cols; ++j)
    {
        sum += frame.at<uchar>(0, j);
        integral_.at<int>(0, j) = sum;
    }

    for (int i = 1; i < frame.rows; ++i)
    {
        sum = 0;

        for (int j = 0; j < frame.cols; ++j)
        {
            sum += frame.at<uchar>(i, j);
            integral_.at<int>(i, j) = sum + integral_.at<int>(i-1, j);
        }
    }
}