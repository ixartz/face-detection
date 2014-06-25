//
//  weak-classifier.h
//  face-detection
//
//  Created by Ixi on 20/06/14.
//
//

#ifndef __face_detection__weak_classifier__
#define __face_detection__weak_classifier__

#include <iostream>
#include <opencv2/opencv.hpp>
#include "feature.h"

class WeakClassifier
{
public:
    WeakClassifier(float threshold,
                   float left_val,
                   float right_val,
                   Feature* feature);

    float calculate_value(cv::Mat& frame_integral,
                          cv::Mat& frame_squared,
                          int j,
                          int i,
                          int size);

protected:
    template <typename T>
    T rectangle_sum(cv::Mat& i, int x1, int y1, int x2, int y2);

protected:
    float threshold_;
    float left_val_;
    float right_val_;
    Feature* feature_;
};

template <typename T>
T WeakClassifier::rectangle_sum(cv::Mat& i, int x1, int y1, int x2, int y2)
{
    /* img.at<uchar>(y, x); */
    T a = i.at<T>(y1, x1);
    T b = i.at<T>(y1, x2);
    T c = i.at<T>(y2, x1);
    T d = i.at<T>(y2, x2);

    return d + a - b - c;
}

#endif /* defined(__face_detection__weak_classifier__) */
