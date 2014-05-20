#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture capture(0);
    cv::Mat cameraFrame;

    capture.read(cameraFrame);

    cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    cv::imshow("Face detection", cameraFrame);

    cv::waitKey(0);

    return EXIT_SUCCESS;
}