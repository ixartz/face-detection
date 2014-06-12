function(add_dir directory return)
  file(GLOB source
     "${directory}/*.h"
     "${directory}/*.cpp"
  )

  if (${directory} STREQUAL ".")
    set(group "root")
  else()
    set(group ${directory})
  ENDIF()

  source_group(${group} FILES ${source})

  set(${return} ${source} PARENT_SCOPE)
endfunction(add_dir)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic -std=c++11")

add_dir("pipeline" source_pipeline)
add_dir("skin-detection" source_skin)
add_dir("facial-feature" source_feature)

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})

add_executable(detection main/detection.cpp ${source_pipeline} ${source_skin})
add_executable(skin-detection main/skin-detection.cpp
               ${source_pipeline} ${source_skin})
add_executable(facial-feature main/facial-feature.cpp
               ${source_pipeline} ${source_feature})

target_link_libraries(detection ${OpenCV_LIBS}
                      ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

target_link_libraries(skin-detection ${OpenCV_LIBS}
                      ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

target_link_libraries(facial-feature ${OpenCV_LIBS}
                      ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})
