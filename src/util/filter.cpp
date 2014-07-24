//
//  filter.cpp
//  face-detection
//
//  Created by Ixi on 13/06/14.
//
//

#include "filter.h"

Filter::Filter()
{

}

Filter::Filter(const cv::Size& size, int type)
    : result_(size, type)
{

}