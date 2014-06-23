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

    read_feature(cascade["features"]);

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

    for (; it_classifier != it_classifier_end; ++it_classifier)
    {
        read_weak_classifier(s, it_classifier);
    }

    h->get_stage_array().push_back(s);
}

void FtData::read_feature(const cv::FileNode& feature_node)
{
    cv::FileNodeIterator it = feature_node.begin(), it_end = feature_node.end();

    for (; it != it_end; ++it)
    {
        Feature feature;
        read_rectangle(feature, it);
        feature_array_.push_back(feature);
    }
}

void FtData::read_rectangle(Feature& feature, cv::FileNodeIterator& it)
{
    cv::FileNode e = (*it)["rects"];
    cv::FileNodeIterator it_e = e.begin(), it_e_end = e.end();

    for (; it_e != it_e_end; ++it_e)
    {
        cv::FileNodeIterator it_rect = (cv::FileNodeIterator)(*it_e).begin();

        cv::Point p1;
        cv::Point p2;
        p1.x = *(it_rect);
        p1.y = *(it_rect += 1);
        p2.x = *(it_rect += 1);
        p2.y = *(it_rect += 1);

        Rectangle rect(p1, p2, *(it_rect += 1));

        feature.get_rectangle_array().push_back(rect);
    }
}

void FtData::read_weak_classifier(Stage& s, cv::FileNodeIterator& it)
{
    cv::FileNode e = (*it)["internalNodes"];
    cv::FileNodeIterator it_e = e.begin();
    cv::FileNode f = (*it)["leafValues"];
    cv::FileNodeIterator it_f = f.begin();

    it_e += 2;
    int rect_id = (int)*it_e;

    WeakClassifier w(*(it_e += 1),
                     *(it_f),
                     *(it_f += 1),
                     &feature_array_[rect_id]);

    s.get_weak_classifier_array().push_back(w);
}