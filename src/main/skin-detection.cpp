#include <iostream>
#include "../skin-detection/skin-detection.h"
#include "../util/image-process.h"
#include "Config.h"

int main()
{
    SkinDetection d;
    ImageProcess img;
    img.process(d);

    return EXIT_SUCCESS;
}