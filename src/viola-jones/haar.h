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
#include "../util/ft-data.h"
#include "integral.h"
#include "pyramid.h"
#include "stage.h"
#include "Config.h"

class Haar :public Filter
{
public:
    Haar(Camera* c);
    void apply(cv::Mat& frame);
    int rectangle_sum(int x1, int y1, int x2, int y2);
    std::vector<Stage>& get_stage_array();

protected:
    Camera* c_;
    Integral i_;
    Pyramid p_;
    cv::Mat gray_;
    int size_ = 24;
    int step_ = 1;
    FtData data_;
    std::vector<Stage> stage_array_;
};

#endif /* defined(__face_detection__haar__) */
