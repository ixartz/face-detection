//
//  ft-data.h
//  face-detection
//
//  Created by Ixi on 13/06/14.
//
//

#ifndef __face_detection__ft_data__
# define __face_detection__ft_data__

# include <iostream>
# include <opencv2/opencv.hpp>
# include "../viola-jones/stage.h"
# include "../viola-jones/weak-classifier.h"
# include "../viola-jones/feature.h"
# include "../viola-jones/rectangle.h"

class Haar;

class FtData
{
public:
    FtData(const std::string& filename);
    void read(Haar* h);

protected:
    void read_stage(Haar* h, cv::FileNodeIterator& it);
    void read_feature(const cv::FileNode& feature);
    void read_rectangle(Feature& feature, cv::FileNodeIterator& it);
    void read_weak_classifier(Stage& s, cv::FileNodeIterator& it);

protected:
    cv::FileStorage f_;
    std::string filename_;
    std::vector<Feature> feature_array_;
};

#endif /* defined(__face_detection__ft_data__) */
