set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Werror -pedantic -std=c++11")

file(GLOB source
     "*.h"
     "*.cpp"
)

add_executable(detection ${source})
