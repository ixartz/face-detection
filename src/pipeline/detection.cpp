#include "detection.h"

Detection::Detection()
    : color_face_(255, 0, 255)
    , face_cascade_(std::string(PROJECT_SRC_DIR)
                    + "/haarcascade/haarcascade_frontalface_alt.xml")
{
}

void Detection::apply(cv::Mat& frame)
{
    frame.copyTo(skin_);
    cvtColor(frame, gray_, CV_BGR2GRAY);
    equalizeHist(gray_, gray_);

    face_cascade_.detectMultiScale(gray_, faces_, 1.3, 2,
                                   0 | CV_HAAR_SCALE_IMAGE,
                                   cv::Size(30, 30));


    skin_detection_.apply(skin_);

    for (size_t i = 0; i < faces_.size(); ++i)
    {
        if (have_skin(faces_[i]))
        {
            cv::rectangle(frame, cv::Point(faces_[i].x, faces_[i].y),
                          cv::Point(faces_[i].x + faces_[i].width,
                                    faces_[i].y + faces_[i].height),
                          color_face_);
        }
    }
}

bool Detection::have_skin(cv::Rect& face)
{
    for (int i = face.y; i <= face.y + face.height; ++i)
    {
        for (int j = face.x; j <= face.x + face.width; ++j)
        {
            if (skin_.at<cv::Vec3b>(i, j)[0] == 0
                && skin_.at<cv::Vec3b>(i, j)[1] == 0
                && skin_.at<cv::Vec3b>(i, j)[2] == 0)
            {
                return true;
            }
        }
    }

    return false;
}