cmake_minimum_required(VERSION 2.6)
project(apriltags2)

# pull in the pods macros. See cmake/pods.cmake for documentation
set(POD_NAME apriltags2)
include(cmake/pods.cmake)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -Wno-unused-parameter -Wno-unused-function -pthread -I. -Icommon -O1")

file(GLOB SOURCE_FILES "src/*.c")
file(GLOB SOURCE_COMMON_FILES "src/common/*.c")
include_directories(${PROJECT_SOURCE_DIR}/src/common)
add_library(apriltags2 ${SOURCE_FILES} ${SOURCE_COMMON_FILES})
target_link_libraries(apriltags2 pthread m)

pods_install_libraries(apriltags2)

file(GLOB header_files "src/*.h")
pods_install_headers(${header_files} DESTINATION AprilTags2/)
file(GLOB common_header_files "src/common/*.h")
pods_install_headers(${common_header_files} DESTINATION "AprilTags2/common/")

pods_install_pkg_config_file(apriltags2
    LIBS -lapriltags2
    REQUIRES 
    VERSION 1.0.0)

add_executable(apriltags2-demo src/apriltag_demo.c)
target_link_libraries(apriltags2-demo apriltags2)
pods_install_executables(apriltags2-demo)



