//
//  haar.cpp
//  face-detection
//
//  Created by Ixi on 17/06/14.
//
//

#include "haar.h"

Haar::Haar(Camera* c)
    : c_(c)
    , i_(c)
    , data_(std::string(PROJECT_SRC_DIR)
            + "/haarcascade/"
            + "haarcascade_frontalface_default.xml")
{
    data_.read(this);
}

void Haar::apply(cv::Mat& frame)
{
    cv::Rect r;
    cv::Size s;
    cv::Mat frame_gray;
    cv::Mat frame_integral;
    cv::Mat frame_squared;
    cvtColor(frame, frame_gray, CV_BGR2GRAY);
    bool pass;

    for (float factor = 1; ; factor *= 1.25)
    {
        s = cv::Size(frame_gray.cols / factor, frame_gray.rows / factor);

        if (size_ > s.width || size_ > s.height)
            break;

        p_.set_size(s);
        p_.apply(frame_gray);
        frame_gray = p_.get_result();
        i_.apply(frame_gray);
        frame_integral = i_.get_result();
        frame_squared = i_.get_result_squared();

        for (int i = 0; i < frame_gray.rows - size_; i += step_)
        {
            for (int j = 0; j < frame_gray.cols - size_; j += step_)
            {
                pass = true;

                for (auto it = stage_array_.begin();
                     it != stage_array_.end();
                     ++it)
                {
                    if (!it->pass(frame_integral, frame_squared, i, j, size_))
                    {
                        pass = false;
                        break;
                    }
                }

                if (pass)
                {
                    cv::rectangle(frame,
                                  cv::Point(j * factor, i * factor),
                                  cv::Point((j + size_) * factor, (i + size_) * factor),
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