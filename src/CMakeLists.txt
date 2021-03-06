function(add_dir directory return)
  file(GLOB source
     "${directory}/*.h"
     "${directory}/*.cpp"
  )

  if (${directory} STREQUAL ".")
    set(group "root")
  else()
    set(group ${directory})
  endif()

  source_group(${group} FILES ${source})

  set(${return} ${source} PARENT_SCOPE)
endfunction(add_dir)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic -std=c++11")

add_dir("pipeline" source_pipeline)
add_dir("skin-detection" source_skin)
add_dir("facial-feature" source_feature)
add_dir("viola-jones" source_haar)
add_dir("util" source_util)
add_dir("adaboost" source_adaboost)

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(TBB REQUIRED)

include_directories(SYSTEM ${OpenCV_INCLUDE_DIRS})
include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
include_directories(${TBB_INCLUDE_DIRS})

add_executable(detection main/detection.cpp
               ${source_pipeline} ${source_skin} ${source_util})
add_executable(adaboost main/adaboost.cpp
               ${source_adaboost} ${source_util})
add_executable(skin-detection main/skin-detection.cpp
               ${source_skin} ${source_util})
add_executable(facial-feature main/facial-feature.cpp
               ${source_feature} ${source_util})
add_executable(viola-jones main/viola-jones.cpp
               ${source_haar} ${source_util})

target_link_libraries(detection ${OpenCV_LIBS} ${TBB_LIBRARIES}
                      ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

target_link_libraries(adaboost ${OpenCV_LIBS} ${TBB_LIBRARIES}
                      ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

target_link_libraries(skin-detection ${OpenCV_LIBS} ${TBB_LIBRARIES}
                      ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

target_link_libraries(facial-feature ${OpenCV_LIBS} ${TBB_LIBRARIES}
                      ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})

target_link_libraries(viola-jones ${OpenCV_LIBS} ${TBB_LIBRARIES}
                      ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY})
