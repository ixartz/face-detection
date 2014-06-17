//
//  ft.h
//  face-detection
//
//  Created by Ixi on 13/06/14.
//
//

#ifndef __face_detection__ft__
# define __face_detection__ft__

# include <iostream>
# include <opencv2/opencv.hpp>

template <class T>
T load_ft(const std::string& fname)
{
    T x;
    cv::FileStorage f(fname, cv::FileStorage::READ);
    f["ft object"] >> x;
    f.release();

    return x;
}

template<class T>
void read(const cv::FileNode& node,
          T& x,
          const T& d)
{
    if(node.empty())
        x = d;
    else
        x.read(node);
}

#endif /* defined(__face_detection__ft__) */
