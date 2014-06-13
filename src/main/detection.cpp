#include "../pipeline/camera.h"
#include "../pipeline/detection.h"
#include "../util/folder-process.h"

int main(int argc, char* argv[])
{
    Detection d;

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