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
    clock_t init_timer = clock();
    int nb_call = 0;
    
    while (key_ != 'q')
    {
        capture_.read(camera_frame_);
        //cv::flip(camera_frame_, camera_frame_, 1);

        cv::resize(camera_frame_, camera_frame_resized_, camera_size_);
        d.apply(camera_frame_resized_);

        cv::imshow("Face detection", camera_frame_resized_);

        //count frame analized for each second
        if (CLOCKS_PER_SEC >= clock() - init_timer){
            ++nb_call;
        }
        else{
            std::cout << nb_call << " fps" << std::endl;
            nb_call = 1;
            init_timer = clock();
        }
        
        key_ = cvWaitKey(1);
    }
}

cv::Size& Camera::get_camera_size()
{
    return camera_size_;
}