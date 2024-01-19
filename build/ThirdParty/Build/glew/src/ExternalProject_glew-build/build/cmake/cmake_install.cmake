# Install script for directory: S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew/build/cmake

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Install/glew")
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
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/lib/Debug/libglew32d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/lib/Release/libglew32.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/lib/MinSizeRel/libglew32.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/lib/RelWithDebInfo/libglew32.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/lib/Debug/libglew32mxd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/lib/Release/libglew32mx.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/lib/MinSizeRel/libglew32mx.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/lib/RelWithDebInfo/libglew32mx.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES
    "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew/build/cmake/../../glew.pc"
    "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew/build/cmake/../../glewmx.pc"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/GL" TYPE FILE FILES
    "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew/build/cmake/../../include/GL/wglew.h"
    "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew/build/cmake/../../include/GL/glew.h"
    "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew/build/cmake/../../include/GL/glxew.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/glew/glew-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/glew/glew-targets.cmake"
         "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/build/cmake/CMakeFiles/Export/lib/cmake/glew/glew-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/glew/glew-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/glew/glew-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/glew" TYPE FILE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/build/cmake/CMakeFiles/Export/lib/cmake/glew/glew-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/glew" TYPE FILE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/build/cmake/CMakeFiles/Export/lib/cmake/glew/glew-targets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/glew" TYPE FILE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/build/cmake/CMakeFiles/Export/lib/cmake/glew/glew-targets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/glew" TYPE FILE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/build/cmake/CMakeFiles/Export/lib/cmake/glew/glew-targets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/glew" TYPE FILE FILES "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew-build/build/cmake/CMakeFiles/Export/lib/cmake/glew/glew-targets-release.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/glew" TYPE FILE FILES
    "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew/build/cmake/glew-config.cmake"
    "S:/ArtTool/Effekseer_1.51/build/ThirdParty/Build/glew/src/ExternalProject_glew/build/cmake/CopyImportedTargetProperties.cmake"
    )
endif()

