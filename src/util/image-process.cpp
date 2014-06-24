//
//  image-process.cpp
//  face-detection
//
//  Created by Ixi on 24/06/14.
//
//

#include "image-process.h"

ImageProcess::ImageProcess()
    : frame_(cv::imread(std::string(PROJECT_SRC_DIR) + "/img_187.jpg",
                                    CV_LOAD_IMAGE_COLOR))
{
    cv::namedWindow("Skin detection", cv::WINDOW_AUTOSIZE);
}

ImageProcess::~ImageProcess()
{
    cv::destroyWindow("Skin detection");
}

void ImageProcess::process(Filter& d)
{
    d.apply(frame_);
    cv::imshow("Skin detection", frame_);

    cvWaitKey(0);
}