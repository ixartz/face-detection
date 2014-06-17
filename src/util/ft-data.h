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

class FtData
{
public:
    void read(const cv::FileNode& node);
};

#endif /* defined(__face_detection__ft_data__) */
