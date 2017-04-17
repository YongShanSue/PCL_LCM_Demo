find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

find_package(OpenCV)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(rv-tango-tablet-lcm rv-tango-tablet-lcm-multi-cloud.cpp
	lcmgl-util.cpp)
pods_use_pkg_config_packages(rv-tango-tablet-lcm lcm bot2-core eigen3)
target_link_libraries(rv-tango-tablet-lcm 
    rv-cv-bridge-lcm  bot2-lcmgl-client
    ${Boost_FILESYSTEM_LIBRARY} boost_system boost_filesystem
    ${OpenCV_LIBS}
    )
pods_install_executables(rv-tango-tablet-lcm)
