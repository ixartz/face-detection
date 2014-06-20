//
//  ft-data.cpp
//  face-detection
//
//  Created by Ixi on 13/06/14.
//
//

#include "ft-data.h"

FtData::FtData(const std::string& filename)
    : f_(filename, cv::FileStorage::READ)
    , filename_(filename)
{

}

void FtData::read()
{
    cv::FileNode cascade = f_["cascade"];
    std::cout << "Loading haar features - "
              << "width: " << (int)cascade["width"] << " - "
              << "height: " << (int)cascade["height"] << std::endl;
}