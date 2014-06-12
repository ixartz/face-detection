#ifndef CAMERA_H
# define CAMERA_H

# include <opencv2/opencv.hpp>
# include "detection.h"

class Camera
{
public:
    Camera();
    ~Camera();
    void process(Detection& d);

protected:
    cv::VideoCapture capture_;
    cv::Mat camera_frame_;
    cv::Size camera_size_;
    cv::Mat camera_frame_resized_;
    char key_ = 0;
};

#endif /* !CAMERA_H */
