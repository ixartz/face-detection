#include <iostream>
#include "../skin-detection/skin-detection.h"
#include "../util/image-process.h"
#include "../util/camera.h"
#include "Config.h"

int main()
{
    SkinDetection d;

    Camera c;
    c.process(d);

    return EXIT_SUCCESS;
}