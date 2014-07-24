//
//  filter.h
//  face-detection
//
//  Created by Ixi on 13/06/14.
//
//

#ifndef __face_detection__filter__
# define __face_detection__filter__

# include <iostream>
# include <opencv2/opencv.hpp>

class Filter
{
public:
    Filter();
    Filter(const cv::Size& size, int type);
    virtual void apply(cv::Mat& frame) = 0;
    const cv::Mat& get_result() const;

protected:
    cv::Mat result_;
};

inline const cv::Mat&
Filter::get_result() const
{
    return result_;
}

#endif /* defined(__face_detection__filter__) */
