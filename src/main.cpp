#include "boost/filesystem.hpp"
#include "camera.h"
#include "detection.h"

int main(int argc, char* argv[])
{
  Detection d;

  if (argc > 1)
  {
    cv::Mat image;
    std::string output_dir("../output/");
    boost::filesystem::path dir(argv[1]);
    boost::filesystem::directory_iterator end;

    if (boost::filesystem::exists(dir)
        && boost::filesystem::is_directory(dir))
    {
      for (boost::filesystem::directory_iterator it(dir);
           it != end; ++it)
      {
        std::cout << it->path().filename() << std::endl;
        image = cv::imread(it->path().string(), CV_LOAD_IMAGE_COLOR);

        d.apply(image);
        cv::imwrite(output_dir + it->path().filename().string(), image);
      }
    }
  }
  else
  {
    Camera c;

    c.process(d);
  }

  return EXIT_SUCCESS;
}