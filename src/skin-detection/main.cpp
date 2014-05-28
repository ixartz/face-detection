#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "Config.h"

int main()
{
    std::ifstream f(std::string(PROJECT_SRC_DIR) + "/skin/Skin_NonSkin.txt");

    if (!f.is_open())
    {
        std::cout << "No such file" << std::endl;
        return EXIT_FAILURE;
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
    cv::NormalBayesClassifier classifier;
    classifier.train(train, label_train);
    std::cout << "Finished training" << std::endl;

    cv::Mat frame;
    cv::namedWindow("Face detection", cv::WINDOW_AUTOSIZE);
    cv::Mat sample(1, 3, CV_32FC1);
    int res;

    frame = cv::imread(std::string(PROJECT_SRC_DIR) + "/img_136.png", CV_LOAD_IMAGE_COLOR);

    for (int j = 0; j < frame.cols; ++j)
    {
        for (int i = 0; i < frame.rows; ++i)
        {
            sample.at<float>(0, 0) = frame.at<cv::Vec3b>(i, j)[0];
            sample.at<float>(0, 1) = frame.at<cv::Vec3b>(i, j)[1];
            sample.at<float>(0, 2) = frame.at<cv::Vec3b>(i, j)[2];

            res = classifier.predict(sample);

            if (res == 1)
            {
                frame.at<cv::Vec3b>(i, j)[0] = 255;
                frame.at<cv::Vec3b>(i, j)[1] = 255;
                frame.at<cv::Vec3b>(i, j)[2] = 255;
            }
            else
            {
                frame.at<cv::Vec3b>(i, j)[0] = 0;
                frame.at<cv::Vec3b>(i, j)[1] = 0;
                frame.at<cv::Vec3b>(i, j)[2] = 0;
            }
        }
    }

    cv::imshow("Face detection", frame);

    cvWaitKey(0);

    /*
    cv::VideoCapture capture_(0);
    cv::Mat camera_frame_;
    char key_ = 0;
    cv::Mat sample(1, 3, CV_32FC1);
    int res;

    cv::namedWindow("Face detection", cv::WINDOW_AUTOSIZE);

    while (key_ != 'q')
    {
        capture_.read(camera_frame_);
        //cv::flip(camera_frame_, camera_frame_, 1);

        for (int j = 0; j < camera_frame_.cols; ++j)
        {
            for (int i = 0; i < camera_frame_.rows; ++i)
            {
                sample.at<float>(0, 0) = camera_frame_.at<cv::Vec3b>(i, j)[0];
                sample.at<float>(0, 1) = camera_frame_.at<cv::Vec3b>(i, j)[1];
                sample.at<float>(0, 2) = camera_frame_.at<cv::Vec3b>(i, j)[2];

                res = classifier.predict(sample);

                std::cout << res << std::endl;
            }
        }

        cv::imshow("Face detection", camera_frame_);

        key_ = cvWaitKey(10);
    }
    */

    return EXIT_SUCCESS;
}