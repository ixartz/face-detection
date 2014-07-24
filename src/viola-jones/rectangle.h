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
    const cv::Point& get_p1() const;
    const cv::Point& get_p2() const;
    float get_weight();

protected:
    cv::Point p1_;
    cv::Point p2_; // p2 is the rectangle size
    float weight_;
};

inline const cv::Point&
Rectangle::get_p1() const
{
    return p1_;
}

inline const cv::Point&
Rectangle::get_p2() const
{
    return p2_;
}

inline float
Rectangle::get_weight()
{
    return weight_;
}

#endif /* defined(__face_detection__rectangle__) */
