int main()
{
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
}