#include "camera.h"

Camera::Camera()
  : capture_(0)
{
  cv::namedWindow("Face detection", cv::WINDOW_AUTOSIZE);
}

Camera::~Camera()
{
  cv::destroyWindow("Face detection");
}

void Camera::process(Detection& d)
{
  while (key_ != 'q')
  {
    capture_.read(camera_frame_);
    //cv::flip(camera_frame_, camera_frame_, 1);

    d.apply(camera_frame_);

    cv::imshow("Face detection", camera_frame_);

    key_ = cvWaitKey(10);
  }
}