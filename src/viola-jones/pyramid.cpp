//
//  pyramid.cpp
//  face-detection
//
//  Created by Ixi on 18/06/14.
//
//

#include "pyramid.h"

void Pyramid::apply(cv::Mat& frame)
{
    cv::resize(frame, result_, size_, 0, 0, cv::INTER_LINEAR);
}

void Pyramid::apply(cv::Mat& frame, cv::Mat& dst)
{
    cv::resize(frame, dst, size_, 0, 0, cv::INTER_LINEAR);
}

void Pyramid::set_size(cv::Size& size)
{
    size_ = size;
}

cv::Mat& Pyramid::get_result()
{
    return result_;
}