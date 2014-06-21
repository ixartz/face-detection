#include <iostream>
#include "../util/camera.h"
#include "../viola-jones/haar.h"

int main()
{
    Camera c;
    Haar d(&c);

    c.process(d);

    return EXIT_SUCCESS;
}