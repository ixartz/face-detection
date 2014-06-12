//
//  folder-process.h
//  face-detection
//
//  Created by Ixi on 13/06/14.
//
//

#ifndef __face_detection__folder_process__
#define __face_detection__folder_process__

#include <iostream>
#include "Config.h"
#include "boost/filesystem.hpp"
#include "detection.h"

class FolderProcess
{
public:
    FolderProcess(Detection* d,
                  const std::string& in,
                  const std::string& out);
    void apply();

private:
    std::string project_src_;
    std::string output_dir_;
    boost::filesystem::path input_dir_;
    Detection* d_;
};

#endif /* defined(__face_detection__folder_process__) */
