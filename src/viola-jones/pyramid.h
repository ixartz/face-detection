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
    void set_size(cv::Size& size);
    cv::Mat& get_result();

private:
    cv::Mat result_;
    cv::Size size_;
};

#endif /* defined(__face_detection__pyramid__) */
