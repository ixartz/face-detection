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
    data_.read();
}

void Haar::apply(cv::Mat& frame)
{
    cv::Rect r;
    cv::Size s;

    cvtColor(frame, frame, CV_BGR2GRAY);

    for (float factor = 1; ; factor *= 1.25)
    {
        s = cv::Size(frame.cols / factor, frame.rows / factor);

        if (size_ > s.width || size_ > s.height)
            break;

        p_.set_size(s);
        p_.apply(frame);
        frame = p_.get_result();
        i_.apply(frame);

        for (int i = 0; i < frame.rows - size_; i += step_)
        {
            for (int j = 0; j < frame.cols - size_; j += step_)
            {
                r = cv::Rect(j, i, size_, size_);
            }
        }
    }
}

int Haar::rectangle_sum(int x1, int y1, int x2, int y2)
{
    int a = i_.get_result().at<int>(x1 - 1, y1 - 1);
    int b = i_.get_result().at<int>(x2, y1 - 1);
    int c = i_.get_result().at<int>(x1 - 1, y2);
    int d = i_.get_result().at<int>(x2, y2);

    return d + a - b - c;
}