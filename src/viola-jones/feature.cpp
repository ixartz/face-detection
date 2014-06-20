//
//  feature.cpp
//  face-detection
//
//  Created by Ixi on 21/06/14.
//
//

#include "feature.h"

Feature::Feature(cv::Point& p1, cv::Point& p2, float weight)
    : p1_(p1)
    , p2_(p2)
    , weight_(weight)
{

}