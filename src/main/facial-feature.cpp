#include "../util/folder-process.h"
#include "../facial-feature/facial-feature.h"

int main()
{
    FacialFeature d;
    FolderProcess f(&d, "/jpg/", "/output/");
    f.apply();
}