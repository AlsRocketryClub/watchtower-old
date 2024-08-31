# Install script for directory: D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/modules/mosquitto

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Watchtower")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/mosquitto" TYPE FILE FILES
    "D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/modules/mosquitto/mosquitto.conf"
    "D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/modules/mosquitto/aclfile.example"
    "D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/modules/mosquitto/pskfile.example"
    "D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/modules/mosquitto/pwfile.example"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/watchtower-production/build/mosquitto/libmosquitto.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/watchtower-production/build/mosquitto/libmosquittopp.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/watchtower-production/build/mosquitto/lib/cmake_install.cmake")
  include("D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/watchtower-production/build/mosquitto/client/cmake_install.cmake")
  include("D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/watchtower-production/build/mosquitto/src/cmake_install.cmake")
  include("D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/watchtower-production/build/mosquitto/apps/cmake_install.cmake")
  include("D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/watchtower-production/build/mosquitto/plugins/cmake_install.cmake")
  include("D:/D drive Documents/GitHub/Code-Dei-Tech/Repos/arc-watchtower-hans/watchtower-production/build/mosquitto/man/cmake_install.cmake")

endif()

