#ifndef DETECTION_H
# define DETECTION_H

# include <opencv2/opencv.hpp>
# include "filter.h"
# include "../skin-detection/skin-detection.h"
# include "Config.h"

class Detection : public Filter
{
public:
    Detection();
    void apply(cv::Mat& frame);
    bool have_skin(cv::Rect& face);

protected:
    cv::Mat gray_;
    cv::Mat skin_;
    std::vector<cv::Rect> faces_;
    cv::Scalar color_face_;

    cv::CascadeClassifier face_cascade_;
    SkinDetection skin_detection_;
};

#endif /* !DETECTION_H */
