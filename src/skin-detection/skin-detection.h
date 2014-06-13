//
//  detection.h
//  face-detection
//
//  Created by Ixi on 12/06/14.
//
//

#ifndef __face_detection__detection__
# define __face_detection__detection__

# include <iostream>
# include <fstream>
# include <opencv2/opencv.hpp>
# include "../util/filter.h"
# include "Config.h"

class SkinDetection : public Filter
{
public:
    SkinDetection();
    void apply(cv::Mat& frame);

protected:
    cv::NormalBayesClassifier classifier_;
    cv::Mat sample_;
    int res_;
};

#endif /* defined(__face_detection__detection__) */
