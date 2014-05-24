#include "detection.h"

Detection::Detection()
  : color_face_(255, 0, 255)
  , color_eye_(255, 0, 0)
  , face_cascade_("../haarcascade/haarcascade_frontalface_alt.xml")
  , eye_cascade_("../haarcascade/haarcascade_eye_tree_eyeglasses.xml")
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

      faceROI_ = gray_(faces_[i]);
      eyes_.clear();

      eye_cascade_.detectMultiScale(faceROI_, eyes_, 1.3, 2,
                                    0 | CV_HAAR_SCALE_IMAGE,
                                    cv::Size(30, 30));

      for (size_t j = 0; j < eyes_.size(); ++j)
      {
          cv::Point center(faces_[i].x + eyes_[j].x + eyes_[j].width * 0.5,
                           faces_[i].y + eyes_[j].y + eyes_[j].height * 0.5);
          int radius = cvRound((eyes_[j].width + eyes_[j].height) * 0.25);
          cv::circle(camera_frame, center, radius, color_eye_, 4, 8, 0);

          eyeROI_ = gray_(eyes_[0]);
      }
  }
}