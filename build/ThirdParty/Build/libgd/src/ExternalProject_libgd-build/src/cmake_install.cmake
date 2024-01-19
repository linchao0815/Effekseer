# Install script for directory: S:/ArtTool/Effekseer_1.51/Downloads/libgd/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Install/libgd")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/Debug/gdcmpgif.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/Release/gdcmpgif.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/MinSizeRel/gdcmpgif.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/RelWithDebInfo/gdcmpgif.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/Debug/gd2copypal.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/Release/gd2copypal.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/MinSizeRel/gd2copypal.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/RelWithDebInfo/gd2copypal.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/Debug/gd2togif.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/Release/gd2togif.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/MinSizeRel/gd2togif.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/RelWithDebInfo/gd2togif.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/Debug/giftogd2.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/Release/giftogd2.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/MinSizeRel/giftogd2.exe")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/RelWithDebInfo/giftogd2.exe")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/Debug/libgd_staticd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/Release/libgd_static.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/MinSizeRel/libgd_static.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/Bin/RelWithDebInfo/libgd_static.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/bdftogd")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/entities.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gd.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gd_color_map.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gd_errors.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gd_io.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gdcache.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gdfontg.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gdfontl.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gdfontmb.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gdfonts.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gdfontt.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gdfx.h"
    "S:/ArtTool/Effekseer_1.51/Downloads/libgd/src/gdpp.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/libgd/src/ExternalProject_libgd-build/src/gdlib.pc")
endif()

