#include <iostream>
#include "../util/camera.h"
#include "../util/image-process.h"
#include "../viola-jones/haar.h"

int main()
{
    /*
    Camera c;
    Haar d(&c);

    c.process(d);
    */

    ImageProcess img;
    Haar d(img.get_size());
    img.process(d);

    return EXIT_SUCCESS;
}