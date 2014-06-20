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

class Haar;

class FtData
{
public:
    FtData(const std::string& filename);
    void read(Haar* h);

protected:
    cv::FileStorage f_;
    std::string filename_;
};

#endif /* defined(__face_detection__ft_data__) */
