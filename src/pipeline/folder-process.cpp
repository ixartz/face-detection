//
//  folder-process.cpp
//  face-detection
//
//  Created by Ixi on 13/06/14.
//
//

#include "folder-process.h"

FolderProcess::FolderProcess(Detection* d,
                             const std::string& in,
                             const std::string& out)
    : project_src_(std::string(PROJECT_SRC_DIR))
    , output_dir_(std::string(PROJECT_SRC_DIR) + out)
    , input_dir_(std::string(PROJECT_SRC_DIR) + in)
    , d_(d)
{

}

void FolderProcess::apply()
{
    cv::Mat image;
    boost::filesystem::directory_iterator end;

    if (boost::filesystem::exists(input_dir_)
        && boost::filesystem::is_directory(input_dir_))
    {
        for (boost::filesystem::directory_iterator it(input_dir_);
             it != end; ++it)
        {
            std::cout << it->path().filename() << std::endl;
            image = cv::imread(it->path().string(), CV_LOAD_IMAGE_COLOR);

            d_->apply(image);
            cv::imwrite(output_dir_ + it->path().filename().string(), image);
        }
    }
}