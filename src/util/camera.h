#ifndef CAMERA_H
# define CAMERA_H

# include <opencv2/opencv.hpp>
# include <tbb/concurrent_queue.h>
# include "../util/filter.h"

class Camera
{
public:
    Camera();
    ~Camera();
    void process(Filter& d);
    cv::Size& get_camera_size();

protected:
    cv::VideoCapture capture_;
    cv::Mat camera_frame_;
    cv::Size camera_size_;
    cv::Mat camera_frame_resized_;
    char key_ = 0;
};

#endif /* !CAMERA_H */
