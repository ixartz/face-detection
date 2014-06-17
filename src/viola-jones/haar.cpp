//
//  haar.cpp
//  face-detection
//
//  Created by Ixi on 17/06/14.
//
//

#include "haar.h"

Haar::Haar(Camera* c)
    : c_(c)
    , i_(c)
{
}

void Haar::apply(cv::Mat& frame)
{
    cvtColor(frame, frame, CV_BGR2GRAY);
    i_.apply(frame);
}