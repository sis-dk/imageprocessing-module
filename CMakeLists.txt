cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
set("OpenCV_DIR" "/usr/local/opencv/lib/cmake/opencv4")
set("OpenCV_INCLUDE_DIRS" "/usr/local/opencv/include/opencv4")

project(imageprocessing)

file(GLOB opencv_libss "/usr/local/opencv/lib/*.a" "/usr/local/opencv/lib/opencv4/3rdparty/*.a")

file(GLOB SOURCE_FILES "src/*.cc" "src/*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC} ${OpenCV_INCLUDE_DIRS})

# Essential library files to link to a node addon
# You should add this line in every CMake.js based project
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} ${opencv_libss})
