//
//  image-process.h
//  face-detection
//
//  Created by Ixi on 24/06/14.
//
//

#ifndef __face_detection__image_process__
#define __face_detection__image_process__

#include <iostream>
#include <opencv2/opencv.hpp>
#include "Config.h"
#include "filter.h"

class ImageProcess
{
public:
    ImageProcess();
    ~ImageProcess();
    void process(Filter& d);
    cv::Size get_size();

protected:
    cv::Mat frame_;
};

#endif /* defined(__face_detection__image_process__) */
