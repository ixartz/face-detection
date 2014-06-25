//
//  haar.cpp
//  face-detection
//
//  Created by Ixi on 17/06/14.
//
//

#include "haar.h"

Haar::Haar(Camera* c)
    : Haar(c->get_camera_size())
{

}

Haar::Haar(const cv::Size& camera_size)
    : frame_integral_(camera_size, CV_32SC1)
    , frame_squared_(camera_size, CV_64FC1)
    , camera_size_(camera_size)
    , i_(camera_size)
    , data_(std::string(PROJECT_SRC_DIR)
            + "/haarcascade/"
            + "haarcascade_frontalface_default.xml")
{
    data_.read(this);
}

void Haar::apply(cv::Mat& frame)
{
    cvtColor(frame, frame_gray_, CV_BGR2GRAY);
    bool pass;

    for (float factor = 1; ; factor *= 1.25)
    {
        s_.width = frame_gray_.cols / factor;
        s_.height = frame_gray_.rows / factor;

        if (size_ > s_.width || size_ > s_.height)
            break;

        p_.set_size(s_);
        p_.apply(frame_gray_, frame_resized_);
        i_.apply(frame_resized_, frame_integral_, frame_squared_);

        for (int i = 0; i < frame_resized_.rows - size_; i += step_)
        {
            for (int j = 0; j < frame_resized_.cols - size_; j += step_)
            {
                pass = true;

                for (auto it = stage_array_.begin();
                     it != stage_array_.end();
                     ++it)
                {
                    if (!it->pass(frame_integral_, frame_squared_, j, i, size_))
                    {
                        pass = false;
                        break;
                    }
                }

                if (pass)
                {
                    cv::rectangle(frame,
                                  cv::Point(j * factor, i * factor),
                                  cv::Point((j + size_) * factor,
                                            (i + size_) * factor),
                                  cv::Scalar(255, 0, 255));
                }
            }
        }
    }
}

std::vector<Stage>& Haar::get_stage_array()
{
    return stage_array_;
}