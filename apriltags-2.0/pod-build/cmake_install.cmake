# Install script for directory: /home/robotvision/code/assistive-robotics-repo/apriltags-2.0

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/robotvision/code/build")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/pod-build/lib/libapriltags2.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/AprilTags2" TYPE FILE FILES
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/tag36artoolkit.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/tag16h5.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/g2d.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/tag25h7.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/tag25h9.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/apriltag.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/tag36h10.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/tag36h11.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/AprilTags2/common" TYPE FILE FILES
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/time_util.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/image_u32.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/zhash.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/zmaxheap.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/workerpool.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/svd22.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/math_util.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/matd.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/string_util.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/postscript_utils.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/image_f32.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/getopt.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/zarray.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/pnm.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/image_u8.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/timeprofile.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/homography.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/src/common/unionfind.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/pod-build/lib/pkgconfig/apriltags2.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/apriltags2-demo" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/apriltags2-demo")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/apriltags2-demo"
         RPATH "/home/robotvision/code/build/lib")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/pod-build/bin/apriltags2-demo")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/apriltags2-demo" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/apriltags2-demo")
    FILE(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/apriltags2-demo"
         OLD_RPATH "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/pod-build/lib:/home/robotvision/code/build/lib:"
         NEW_RPATH "/home/robotvision/code/build/lib")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/apriltags2-demo")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/pod-build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/robotvision/code/assistive-robotics-repo/apriltags-2.0/pod-build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
