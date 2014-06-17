#include "camera.h"

Camera::Camera()
    : capture_(0)
{
    cv::namedWindow("Face detection", cv::WINDOW_AUTOSIZE);

    capture_.read(camera_frame_);

    camera_size_ = cv::Size(camera_frame_.cols / 2,
                            camera_frame_.rows / 2);

    camera_frame_resized_ = cv::Mat(camera_size_, CV_8UC3);
}

Camera::~Camera()
{
    cv::destroyWindow("Face detection");
}

void Camera::process(Filter& d)
{
    while (key_ != 'q')
    {
        capture_.read(camera_frame_);
        //cv::flip(camera_frame_, camera_frame_, 1);

        cv::resize(camera_frame_, camera_frame_resized_, camera_size_);
        d.apply(camera_frame_resized_);

        cv::imshow("Face detection", camera_frame_resized_);

        key_ = cvWaitKey(10);
    }
}