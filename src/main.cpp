#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture capture(0);
    cv::Mat camera_frame;
    cv::Mat camera_frame_gray;
    std::vector<cv::Rect> faces;
    char key = 0;

    cv::CascadeClassifier face_cascade("../haarcascade_frontalface_default.xml");
    cv::CascadeClassifier eye_cascade("../haarcascade_eye.xml");

    cv::namedWindow("Face detection", cv::WINDOW_AUTOSIZE);

    while (key != 'q')
    {
        capture.read(camera_frame);
        cv::flip(camera_frame, camera_frame, 1);
        cvtColor(camera_frame, camera_frame_gray, CV_BGR2GRAY);

        face_cascade.detectMultiScale(camera_frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

        for (size_t i = 0; i < faces.size(); ++i)
        {
            cv::Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);
            cv::ellipse(camera_frame, center, cv::Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
        }

        cv::imshow("Face detection", camera_frame);

        key = cvWaitKey(1000 / 30);
    }

    cv::destroyWindow("Face detection");

    return EXIT_SUCCESS;
}