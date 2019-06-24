cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")
set("OpenCV_DIR" "/usr/local/opencv/lib/cmake/opencv4")
set("OpenCV_INCLUDE_DIRS" "/usr/local/opencv/include/opencv4")

project(imageprocessing)

# find_package(OpenCV REQUIRED)

message( "The opencv dir issss" )
message( ${OpenCV_DIR} )
message( "The opencv includes areeeeeee" )
message( ${OpenCV_INCLUDE_DIRS} )

file(GLOB opencv_libss "/usr/local/opencv/lib/*.a" "/usr/local/opencv/lib/opencv4/3rdparty/*.a")

message( "The opencv libs areeeeeee" )
message( ${opencv_libss} )

file(GLOB SOURCE_FILES "src/*.cc" "src/*.h")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC} ${OpenCV_INCLUDE_DIRS})

# Essential library files to link to a node addon
# You should add this line in every CMake.js based project
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB} ${opencv_libss})
