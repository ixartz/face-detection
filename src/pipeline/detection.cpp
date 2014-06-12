#include "detection.h"

Detection::Detection()
    : color_face_(255, 0, 255)
    , face_cascade_(std::string(PROJECT_SRC_DIR) + "/haarcascade/haarcascade_frontalface_alt.xml")
{

}

void Detection::apply(cv::Mat& camera_frame)
{
    cvtColor(camera_frame, gray_, CV_BGR2GRAY);
    equalizeHist(gray_, gray_);

    face_cascade_.detectMultiScale(gray_, faces_, 1.3, 2,
                                   0 | CV_HAAR_SCALE_IMAGE,
                                   cv::Size(30, 30));

    for (size_t i = 0; i < faces_.size(); ++i)
    {
        cv::Point center(faces_[i].x + faces_[i].width * 0.5,
                         faces_[i].y + faces_[i].height * 0.5);

        cv::ellipse(camera_frame, center,
                    cv::Size(faces_[i].width * 0.5, faces_[i].height * 0.5),
                    0, 0, 360, color_face_, 4, 8, 0);

        face_ROI_ = gray_(faces_[i]);
    }
}