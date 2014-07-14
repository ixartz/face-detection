#include "camera.h"

Camera::Camera()
    : capture_(0)
{
    cv::namedWindow("Face detection", cv::WINDOW_AUTOSIZE);

    capture_.read(camera_frame_);

    camera_size_ = cv::Size(camera_frame_.cols / 2,
                            camera_frame_.rows / 2);

    //CV_8UC3 = 8 bits + 3 channels
    camera_frame_resized_ = cv::Mat(camera_size_, CV_8UC3);
}

Camera::~Camera()
{
    cv::destroyWindow("Face detection");
}

void Camera::process(Filter& d)
{
    tbb::parallel_pipeline(4,
        tbb::make_filter<void, Camera*>(
            tbb::filter::serial_in_order,
            [this](tbb::flow_control& fc)
            {
                capture_.read(camera_frame_);

                key_ = cvWaitKey(10);

                if (key_ == 'q')
                {
                    fc.stop();
                }

                return this;
            }) &
        tbb::make_filter<Camera*, Camera*>(
            tbb::filter::parallel,
            [](Camera* c)
            {
                cv::resize(c->camera_frame_,
                           c->camera_frame_resized_,
                           c->camera_size_);
                return c;
            }) &
        tbb::make_filter<Camera*, Camera*>(
            tbb::filter::serial_in_order,
            [&d](Camera* c)
            {
                d.apply(c->camera_frame_resized_);
                return c;
            }) &
        tbb::make_filter<Camera*,void>(
            tbb::filter::serial_in_order,
            [](Camera* c)
            {
                cv::imshow("Face detection", c->camera_frame_resized_);
            })
    );
}

cv::Size& Camera::get_camera_size()
{
    return camera_size_;
}