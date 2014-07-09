#include <iostream>
#include "../util/camera.h"
#include "../util/folder-process.h"
#include "../util/image-process.h"
#include "../viola-jones/haar.h"

int main()
{
    Camera c;
    Haar d(&c);
    c.process(d);

    /*
    ImageProcess img;
    Haar d(img.get_size());
    img.process(d);
    */

    /*
    Haar d(cv::Size(999999, 999999));
    FolderProcess f(&d, "/input/", "/output/");
    f.apply();
    */

    return EXIT_SUCCESS;
}