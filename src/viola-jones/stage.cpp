//
//  stage.cpp
//  face-detection
//
//  Created by Ixi on 20/06/14.
//
//

#include "stage.h"

Stage::Stage(int nb_weak, float threshold)
    : nb_weak_(nb_weak)
    , threshold_(threshold)
{
}

bool Stage::pass(cv::Mat& frame_integral,
                 cv::Mat& frame_squared,
                 int j,
                 int i,
                 int size)
{
    float sum = 0;

    for (auto it = weak_classifier_array_.begin();
         it != weak_classifier_array_.end();
         ++it)
    {
        sum += it->calculate_value(frame_integral, frame_squared, j, i, size);
    }

    return sum > threshold_;
}

std::vector<WeakClassifier>& Stage::get_weak_classifier_array()
{
    return weak_classifier_array_;
}