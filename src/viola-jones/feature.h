//
//  feature.h
//  face-detection
//
//  Created by Ixi on 21/06/14.
//
//

#ifndef __face_detection__feature__
#define __face_detection__feature__

#include <iostream>
#include <opencv2/opencv.hpp>

class Feature
{
public:
    Feature(cv::Point& p1, cv::Point& p2, float weight);

protected:
    cv::Point p1_;
    cv::Point p2_;
    float weight_;
};

#endif /* defined(__face_detection__feature__) */
