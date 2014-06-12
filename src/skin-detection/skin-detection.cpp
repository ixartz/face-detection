//
//  detection.cpp
//  face-detection
//
//  Created by Ixi on 12/06/14.
//
//

#include "skin-detection.h"

SkinDetection::SkinDetection()
    : sample_(1, 3, CV_32FC1)
{
    std::ifstream f(std::string(PROJECT_SRC_DIR) + "/skin/Skin_NonSkin.txt");

    if (!f.is_open())
    {
        std::cout << "No such file" << std::endl;
    }

    std::string line;
    int nb_line = 0;

    while (getline(f, line))
        ++nb_line;

    std::stringstream ss;
    int b, g, r, decision;
    cv::Mat train(nb_line, 3, CV_32FC1);
    cv::Mat label_train(nb_line, 1, CV_32FC1);

    nb_line = 0;
    f.clear();
    f.seekg(0, std::ios::beg);

    while (getline(f, line))
    {
        ss = std::stringstream(line);
        ss >> b >> g >> r >> decision;
        train.at<float>(nb_line, 0) = b;
        train.at<float>(nb_line, 1) = g;
        train.at<float>(nb_line, 2) = r;
        label_train.at<float>(nb_line, 0) = decision;
        ++nb_line;
    }

    std::cout << "Starting training" << std::endl;
    classifier_.train(train, label_train);
    std::cout << "Finished training" << std::endl;
}

void SkinDetection::apply(cv::Mat& frame)
{
    for (int i = 0; i < frame.rows; ++i)
    {
        for (int j = 0; j < frame.cols; ++j)
        {
            sample_.at<float>(0, 0) = frame.at<cv::Vec3b>(i, j)[0];
            sample_.at<float>(0, 1) = frame.at<cv::Vec3b>(i, j)[1];
            sample_.at<float>(0, 2) = frame.at<cv::Vec3b>(i, j)[2];

            res_ = classifier_.predict(sample_);

            if (res_ == 1)
            {
                frame.at<cv::Vec3b>(i, j)[0] = 0;
                frame.at<cv::Vec3b>(i, j)[1] = 0;
                frame.at<cv::Vec3b>(i, j)[2] = 0;
            }
            else
            {
                frame.at<cv::Vec3b>(i, j)[0] = 255;
                frame.at<cv::Vec3b>(i, j)[1] = 255;
                frame.at<cv::Vec3b>(i, j)[2] = 255;
            }
        }
    }
}