//
//  weak-classifier.cpp
//  face-detection
//
//  Created by Ixi on 20/06/14.
//
//

#include "weak-classifier.h"

WeakClassifier::WeakClassifier(const cv::Point& p1,
                               const cv::Point& p2,
                               float left_val,
                               float right_val)
    : p1_(p1)
    , p2_(p2)
    , left_val_(left_val)
    , right_val_(right_val)
{

}