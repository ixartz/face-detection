//
//  rectangle.cpp
//  face-detection
//
//  Created by Ixi on 23/06/14.
//
//

#include "rectangle.h"

Rectangle::Rectangle(const cv::Point& p1, const cv::Point& p2, float weight)
    : p1_(p1)
    , p2_(p2)
    , weight_(weight)
{

}

cv::Point& Rectangle::get_p1()
{
    return p1_;
}

cv::Point& Rectangle::get_p2()
{
    return p2_;
}

float Rectangle::get_weight()
{
    return weight_;
}