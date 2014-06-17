//
//  facial-feature.h
//  face-detection
//
//  Created by Ixi on 12/06/14.
//
//

#ifndef __face_detection__facial_feature__
#define __face_detection__facial_feature__

#include <iostream>
#include "../util/filter.h"
#include "../util/ft.h"
#include "../util/ft-data.h"
#include "Config.h"

class FacialFeature : public Filter
{
public:
    FacialFeature();
    void apply(cv::Mat& frame);
};

#endif /* defined(__face_detection__facial_feature__) */
