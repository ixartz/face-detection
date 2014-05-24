#ifndef DETECTION_H
# define DETECTION_H

# include <opencv2/opencv.hpp>

class Detection
{
public:
  Detection();
  void apply(cv::Mat& camera_frame);

protected:
  cv::Mat gray_;
  std::vector<cv::Rect> faces_;
  std::vector<cv::Rect> eyes_;
  cv::Scalar color_face_;
  cv::Scalar color_eye_;
  cv::Mat faceROI_;
  cv::Mat eyeROI_;

  cv::CascadeClassifier face_cascade_;
  cv::CascadeClassifier eye_cascade_;
};

#endif /* !DETECTION_H */
