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
    std::vector<Filter*> v;
    v.push_back(&d);

    process(v);
}

tbb::filter_t<Camera*, Camera*> Camera::make_filter(Filter* f)
{
    tbb::filter_t<Camera*, Camera*> res;

    res = tbb::make_filter<Camera*, Camera*>(
              tbb::filter::serial_in_order,
              [f](Camera* c)
              {
                  f->apply(c->camera_frame_resized_);
                  return c;
              });

    return res;
}

void Camera::process(std::vector<Filter*>& d)
{
    tbb::filter_t<Camera*, Camera*> f = make_filter(*d.begin());

    for (auto& it = d.begin() += 1; it != d.end(); ++it)
    {
        f = f & make_filter(*it);
    }

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
        f &
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