//
//  data_gen.h
//  face-detection
//
//  Created by Nicolas Meny on 23/06/2014.
//
//

#ifndef __face_detection__data_gen__
#define __face_detection__data_gen__

#include "config.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "boost/filesystem.hpp"
#include <vector>

std::vector<float>* data_gen(cv::Mat& classifier);

#endif /* defined(__face_detection__data_gen__) */
