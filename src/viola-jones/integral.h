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
    Integral(cv::Size camera_size);
    void apply(cv::Mat& frame);
    cv::Mat& get_result();
    cv::Mat& get_result_squared();

protected:
    cv::Size camera_size_;
    cv::Mat integral_;
    cv::Mat integral_squared_;
};

#endif /* defined(__face_detection__integral__) */
