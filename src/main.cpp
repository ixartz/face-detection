#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture capture(0);
    cv::Mat cameraFrame;
    char key = 0;

    cv::namedWindow("Face detection", cv::WINDOW_AUTOSIZE);

    while (key != 'q')
    {
        capture.read(cameraFrame);
        cv::flip(cameraFrame, cameraFrame, 1);
        cv::imshow("Face detection", cameraFrame);

        key = cvWaitKey(1000 / 30);
    }

    cv::destroyWindow("Face detection");

    return EXIT_SUCCESS;
}