#include <iostream>
#include "../util/camera.h"
#include "../util/folder-process.h"
#include "../util/image-process.h"
#include "../viola-jones/haar.h"

int main(int argc, char* argv[])
{
    Haar d(cv::Size(999999, 999999));

    if (argc > 1 && std::string(argv[1]) == "test")
    {
        FolderProcess f(&d, "/input/", "/output/");
        f.apply();
    }
    else
    {
        Camera c;
        c.process(d);
    }

    return EXIT_SUCCESS;
}