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
                                      int i,
                                      int j,
                                      int size)
{
    float mean = rectangle_sum(frame_integral, i, j, i + size, j + size)
                 / (size * size);
    float var = rectangle_sum(frame_squared, i, j, i + size, j + size)
                / (size * size) - mean * mean;

    if (var >= 0.)
    {
        var = sqrt(var);
    }
    else
    {
        var = 1.;
    }

    float sum = 0;

    for (auto it = feature_->get_rectangle_array().begin();
         it != feature_->get_rectangle_array().end(); ++it)
    {
        sum += rectangle_sum(frame_integral,
                             i + it->get_p1().x,
                             j + it->get_p1().y,
                             i + it->get_p1().x + it->get_p2().x,
                             j + it->get_p1().y + it->get_p2().y)
               * it->get_weight();
    }

    sum = sum / (size * size);

    if (sum < threshold_ * var)
        return left_val_;
    else
        return right_val_;
}

int WeakClassifier::rectangle_sum(cv::Mat i, int x1, int y1, int x2, int y2)
{
    int a = i.at<int>(x1, y1);
    int b = i.at<int>(x2, y1);
    int c = i.at<int>(x1, y2);
    int d = i.at<int>(x2, y2);

    return d + a - b - c;
}