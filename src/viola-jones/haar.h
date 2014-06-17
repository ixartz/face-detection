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

class Haar :public Filter
{
public:
    Haar(Camera* c);
    void apply(cv::Mat& frame);

protected:
    Camera* c_;
    Integral i_;
    cv::Mat gray_;
};

#endif /* defined(__face_detection__haar__) */
