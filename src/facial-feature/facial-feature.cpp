//
//  facial-feature.cpp
//  face-detection
//
//  Created by Ixi on 12/06/14.
//
//

#include "facial-feature.h"

FacialFeature::FacialFeature()
{
    FtData data = load_ft<FtData>(std::string(PROJECT_SRC_DIR)
                                  + "/muct-landmarks/muct76-opencv.csv");
}

void FacialFeature::apply(cv::Mat& frame)
{

}
