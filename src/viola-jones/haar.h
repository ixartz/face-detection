//
//  haar.h
//  face-detection
//
//  Created by Ixi on 17/06/14.
//
//

#ifndef __face_detection__haar__
#define __face_detection__haar__

#include <iostream>
#include "../util/filter.h"
#include "../util/camera.h"
#include "integral.h"
#include "pyramid.h"

class Haar :public Filter
{
public:
    Haar(Camera* c);
    void apply(cv::Mat& frame);
    int rectangle_sum(int x1, int y1, int x2, int y2);

protected:
    Camera* c_;
    Integral i_;
    Pyramid p_;
    cv::Mat gray_;
    int size_ = 24;
    int step_ = 1;
};

#endif /* defined(__face_detection__haar__) */
