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
                /* img.at<uchar>(i, j); */
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
                    rect_list_.push_back(cv::Rect(j * factor,
                                                  i * factor,
                                                  size_ * factor,
                                                  size_ * factor));
                }
            }
        }
    }

    merge(frame);
}

void Haar::merge(cv::Mat& frame)
{
    size_t i;
    float s;
    int nb_classes = partition(rect_list_, labels_, cv::SimilarRects(0.2));
    rrects_.resize(nb_classes);
    rweights_.resize(nb_classes, 0);

    for (i = 0; i < labels_.size(); ++i)
    {
        int cls = labels_[i];
        rrects_[cls].x += rect_list_[i].x;
        rrects_[cls].y += rect_list_[i].y;
        rrects_[cls].width += rect_list_[i].width;
        rrects_[cls].height += rect_list_[i].height;

        ++rweights_[cls];
    }

    for (i = 0; i < rrects_.size(); ++i)
    {
        s = 1. / rweights_[i];
        rrects_[i].x *= s;
        rrects_[i].y *= s;
        rrects_[i].width *= s;
        rrects_[i].height *= s;
    }

    for (i = 0; i < rrects_.size(); ++i)
    {
        if (rweights_[i] >= 3)
        {
            cv::rectangle(frame,
                          cv::Point(rrects_[i].x, rrects_[i].y),
                          cv::Point(rrects_[i].x + rrects_[i].width,
                                    rrects_[i].y + rrects_[i].height),
                          cv::Scalar(255, 0, 255));
        }
    }

    rect_list_.clear();
    rrects_.clear();
    rweights_.clear();
}