#include <iostream>
#include "../skin-detection/skin-detection.h"
#include "Config.h"

int main()
{
    SkinDetection d;
    cv::Mat frame = cv::imread(std::string(PROJECT_SRC_DIR) + "/img_187.jpg",
                               CV_LOAD_IMAGE_COLOR);

    cv::namedWindow("Skin detection", cv::WINDOW_AUTOSIZE);

    d.apply(frame);
    cv::imshow("Skin detection", frame);

    cvWaitKey(0);

    return EXIT_SUCCESS;
}