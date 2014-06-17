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

class Haar :public Filter
{
    void apply(cv::Mat& frame);
};

#endif /* defined(__face_detection__haar__) */
