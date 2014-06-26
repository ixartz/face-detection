//
//  pyramid.h
//  face-detection
//
//  Created by Ixi on 18/06/14.
//
//

#ifndef __face_detection__pyramid__
#define __face_detection__pyramid__

#include <iostream>
#include <opencv2/opencv.hpp>
#include "../util/filter.h"

class Pyramid : public Filter
{
public:
    void apply(cv::Mat& frame);
    void apply(cv::Mat& frame, cv::Mat& dst);
    void set_size(cv::Size& size);
    const cv::Mat& get_result() const;

private:
    cv::Mat result_;
    cv::Size size_;
};

inline void
Pyramid::apply(cv::Mat& frame)
{
    cv::resize(frame, result_, size_, 0, 0, cv::INTER_LINEAR);
}

inline void
Pyramid::apply(cv::Mat& frame, cv::Mat& dst)
{
    cv::resize(frame, dst, size_, 0, 0, cv::INTER_LINEAR);
}

inline void
Pyramid::set_size(cv::Size& size)
{
    size_ = size;
}

inline const cv::Mat&
Pyramid::get_result() const
{
    return result_;
}

#endif /* defined(__face_detection__pyramid__) */
