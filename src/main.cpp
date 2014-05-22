#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture capture(0);
    cv::Mat camera_frame;
    cv::Mat camera_frame_gray;
    std::vector<cv::Rect> faces;
    std::vector<cv::Rect> eyes;
    cv::Scalar color_face(255, 0, 255);
    cv::Scalar color_eye( 255, 0, 0 );
    cv::Mat faceROI;
    cv::Mat eyeROI;
    char key = 0;

    cv::CascadeClassifier face_cascade("../haarcascade_frontalface_alt.xml");
    cv::CascadeClassifier eye_cascade("../haarcascade_eye_tree_eyeglasses.xml");

    cv::namedWindow("Face detection", cv::WINDOW_AUTOSIZE);

    while (key != 'q')
    {
        capture.read(camera_frame);

        //cv::flip(camera_frame, camera_frame, 1);
        cvtColor(camera_frame, camera_frame_gray, CV_BGR2GRAY);
        equalizeHist(camera_frame_gray, camera_frame_gray);

        face_cascade.detectMultiScale(camera_frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

        for (size_t i = 0; i < faces.size(); ++i)
        {
            cv::Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);
            cv::ellipse(camera_frame, center, cv::Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, 360, color_face, 4, 8, 0);

            faceROI = camera_frame_gray(faces[i]);
            eyes.clear();

            eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, cv::Size(30, 30));

            for (size_t j = 0; j < eyes.size(); ++j)
            {
                cv::Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height * 0.5);
                int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
                cv::circle(camera_frame, center, radius, color_eye, 4, 8, 0);

                eyeROI = camera_frame_gray(eyes[0]);
            }
        }

        cv::imshow("Face detection", camera_frame);

        key = cvWaitKey(10);
    }

    cv::destroyWindow("Face detection");

    return EXIT_SUCCESS;
}