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

    frame = cv::imread(std::string(PROJECT_SRC_DIR) + "/img_315.jpg", CV_LOAD_IMAGE_COLOR);

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

    cv::Mat test;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cvtColor(frame,test, CV_RGB2GRAY);
    cv::findContours( test, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );

    /// Find the rotated rectangles and ellipses for each contour
    std::vector<cv::RotatedRect> minRect( contours.size() );
    std::vector<cv::RotatedRect> minEllipse( contours.size() );

    for( size_t i = 0; i < contours.size(); i++ )
    {
        minRect[i] = minAreaRect( cv::Mat(contours[i]));
        if( contours[i].size() > 5 )
        { minEllipse[i] = cv::fitEllipse( cv::Mat(contours[i]) ); }
    }

    cv::RNG rng(12345);

    cv::Mat drawing = cv::Mat::zeros( frame.size(), CV_8UC3 );
    for(size_t i = 0; i< contours.size(); i++ )
    {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        drawContours( frame, contours, i, color, 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point() );
        cv::ellipse( frame, minEllipse[i], color, 2, 8 );
    }

    cv::imshow("Face detection", frame);

    cvWaitKey(0);

    return EXIT_SUCCESS;
}