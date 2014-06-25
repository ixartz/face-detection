//
//  weak-classifier.cpp
//  face-detection
//
//  Created by Ixi on 20/06/14.
//
//

#include "weak-classifier.h"

WeakClassifier::WeakClassifier(float threshold,
                               float left_val,
                               float right_val,
                               Feature* feature)
    : threshold_(threshold)
    , left_val_(left_val)
    , right_val_(right_val)
    , feature_(feature)
{

}

float WeakClassifier::calculate_value(cv::Mat& frame_integral,
                                      cv::Mat& frame_squared,
                                      int j,
                                      int i,
                                      int size)
{
    double inv_win_area = 1. / (size * size);
    double mean = rectangle_sum<int>(frame_integral,
                                     j,
                                     i,
                                     j + size,
                                     i + size)
                  * inv_win_area;

    double var = rectangle_sum<double>(frame_squared, j, i, j + size, i + size)
                 * inv_win_area - mean * mean;

    if (var >= 1.)
    {
        var = sqrt(var);
    }
    else
    {
        var = 1.;
    }

    int sum = 0;

    for (auto it = feature_->get_rectangle_array().begin();
         it != feature_->get_rectangle_array().end(); ++it)
    {
        sum += rectangle_sum<int>(frame_integral,
                                  j + it->get_p1().x,
                                  i + it->get_p1().y,
                                  j + it->get_p1().x + it->get_p2().x,
                                  i + it->get_p1().y + it->get_p2().y)
               * it->get_weight();
    }

    double sumf = sum * inv_win_area;

    if (sumf < threshold_ * var)
        return left_val_;
    else
        return right_val_;
}