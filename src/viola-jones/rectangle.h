//
//  rectangle.h
//  face-detection
//
//  Created by Ixi on 23/06/14.
//
//

#ifndef __face_detection__rectangle__
#define __face_detection__rectangle__

#include <iostream>
#include <opencv2/opencv.hpp>

class Rectangle
{
public:
    Rectangle(const cv::Point& p1, const cv::Point& p2, float weight);

protected:
    cv::Point p1_;
    cv::Point p2_;
    float weight_;
};

#endif /* defined(__face_detection__rectangle__) */
