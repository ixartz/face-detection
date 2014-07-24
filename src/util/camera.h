#ifndef CAMERA_H
# define CAMERA_H

# include <opencv2/opencv.hpp>
# include <tbb/pipeline.h>
# include "../util/filter.h"

class Camera
{
public:
    Camera();
    ~Camera();
    void process(Filter& d);
    void process(std::vector<Filter*>& d);
    tbb::filter_t<Camera*, Camera*> make_filter(Filter* f);
    cv::Size& get_camera_size();

protected:
    cv::VideoCapture capture_;
    cv::Mat camera_frame_;
    cv::Mat camera_frame_resized_;
    cv::Size camera_size_;
    char key_ = 0;
};

#endif /* !CAMERA_H */
