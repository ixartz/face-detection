#include <iostream>
#include "../util/camera.h"
#include "../viola-jones/haar.h"

int main()
{
    Haar d;

    Camera c;
    c.process(d);

    return EXIT_SUCCESS;
}