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
        read_stage(h, it);
    }
}

void FtData::read_stage(Haar* h, cv::FileNodeIterator& it)
{
    Stage s((int)(*it)["maxWeakCount"],
            (float)(*it)["stageThreshold"]);

    cv::FileNode weak_classifier_array = (*it)["weakClassifiers"];
    cv::FileNodeIterator it_classifier = weak_classifier_array.begin(),
                         it_classifier_end = weak_classifier_array.end();

    h->get_stage_array().push_back(s);

    for (; it_classifier != it_classifier_end; ++it_classifier)
    {
        read_weak_classifier(s, it_classifier);
    }
}

void FtData::read_weak_classifier(Stage& s, cv::FileNodeIterator& it)
{
    cv::FileNode e = (*it)["internalNodes"];
    cv::FileNodeIterator it_e = e.begin(), it_e_end = e.end();

    for (; it_e != it_e_end; ++it_e)
    {
        std::cout << (float)*it_e << std::endl;
    }
}