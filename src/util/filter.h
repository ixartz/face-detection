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
    virtual void apply(cv::Mat& frame) = 0;
};

#endif /* defined(__face_detection__filter__) */
