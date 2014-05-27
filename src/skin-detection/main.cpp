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
    cv::Mat samples(nb_line, 3, CV_32FC1);

    nb_line = 0;
    f.clear();
    f.seekg(0, std::ios::beg);

    while (getline(f, line))
    {
        ss = std::stringstream(line);
        ss >> b >> g >> r >> decision;
        samples.at<float>(nb_line, 0) = b;
        samples.at<float>(nb_line, 1) = g;
        samples.at<float>(nb_line, 2) = r;
        ++nb_line;
    }

    std::cout << "Starting EM training" << std::endl;
    cv::EM em(1);
    em.train(samples);
    std::cout << "Finished training EM" << std::endl;

    return EXIT_SUCCESS;
}