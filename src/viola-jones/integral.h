//
//  integral.h
//  face-detection
//
//  Created by Ixi on 17/06/14.
//
//

#ifndef __face_detection__integral__
#define __face_detection__integral__

#include <iostream>
#include <opencv2/opencv.hpp>
#include "../util/filter.h"
#include "../util/camera.h"

class Integral : public Filter
{
public:
    Integral(Camera* c);
    Integral(const cv::Size& camera_size);
    void apply(cv::Mat& frame);
    void apply(cv::Mat& frame, cv::Mat& integral, cv::Mat& integral_squared);
    const cv::Mat& get_result_squared() const;

protected:
    cv::Size camera_size_;
    cv::Mat integral_squared_;
};

inline void
Integral::apply(cv::Mat& frame)
{
    apply(frame, result_, integral_squared_);
}

inline const cv::Mat&
Integral::get_result_squared() const
{
    return integral_squared_;
}

#endif /* defined(__face_detection__integral__) */
