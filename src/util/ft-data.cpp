//
//  ft-data.cpp
//  face-detection
//
//  Created by Ixi on 13/06/14.
//
//

#include "ft-data.h"
#include "../viola-jones/haar.h"

FtData::FtData(const std::string& filename)
    : f_(filename, cv::FileStorage::READ)
    , filename_(filename)
{

}

void FtData::read(Haar* h)
{
    cv::FileNode cascade = f_["cascade"];
    std::cout << "Loading haar features - "
              << "width: " << (int)cascade["width"] << " - "
              << "height: " << (int)cascade["height"] << std::endl;

    cv::FileNode stages = cascade["stages"];

    cv::FileNodeIterator it = stages.begin(), it_end = stages.end();

    for (; it != it_end; ++it)
    {
        h->get_stage_array().push_back(Stage((int)(*it)["maxWeakCount"],
                                             (float)(*it)["stageThreshold"]));
    }
}