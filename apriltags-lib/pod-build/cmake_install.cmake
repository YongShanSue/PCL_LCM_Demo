# Install script for directory: /home/robotvision/code/assistive-robotics-repo/apriltags-lib

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/pod-build/lib/libapriltags.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/AprilTags" TYPE FILE FILES
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Gridder.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/UnionFindSimple.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Tag36h9.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Tag25h9.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Tag16h5_other.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Tag16h5.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/XYWeight.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/pch.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Segment.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/GLine2D.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Tag25h7.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Tag36h11.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/TagFamily.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Edge.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/GrayModel.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/GLineSegment2D.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Quad.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Gaussian.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/MathUtil.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/TagDetector.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Homography33.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/FloatImage.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/Tag36h11_other.h"
    "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/AprilTags/TagDetection.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/pod-build/lib/pkgconfig/apriltags.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/pod-build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/robotvision/code/assistive-robotics-repo/apriltags-lib/pod-build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
