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

class WeakClassifier
{
public:
    WeakClassifier(const cv::Point& p1,
                   const cv::Point& p2,
                   float left_val,
                   float right_val);

protected:
    cv::Point p1_;
    cv::Point p2_;
    float left_val_;
    float right_val_;
};

#endif /* defined(__face_detection__weak_classifier__) */
