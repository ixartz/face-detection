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
#include "rectangle.h"

class Feature
{
public:
    std::vector<Rectangle>& get_rectangle_array();

protected:
    std::vector<Rectangle> rectangle_array_;
};

#endif /* defined(__face_detection__feature__) */
