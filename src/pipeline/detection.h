#ifndef DETECTION_H
# define DETECTION_H

# include <opencv2/opencv.hpp>
# include "Config.h"

class Detection
{
public:
    Detection();
    void apply(cv::Mat& camera_frame);

protected:
    cv::Mat gray_;
    std::vector<cv::Rect> faces_;
    cv::Scalar color_face_;
    cv::Mat face_ROI_;

    cv::CascadeClassifier face_cascade_;
};

#endif /* !DETECTION_H */
