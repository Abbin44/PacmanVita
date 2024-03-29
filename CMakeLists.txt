cmake_minimum_required(VERSION 2.8)

## This includes the Vita toolchain, must go before project definition
# It is a convenience so you do not have to type
# -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake for cmake. It is
# highly recommended that you include this block for all projects.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

## Define project parameters here
# Name of the project
project(Pacman)
# This line adds Vita helper macros, must go after project definition in order
# to build Vita specific artifacts (self/vpk).
include("${VITASDK}/share/vita.cmake" REQUIRED)

## Configuration options for this app
# Display name (under bubble in LiveArea)
set(VITA_APP_NAME "Pacman")
# Unique ID must be exactly 9 characters. Recommended: XXXXYYYYY where X =
# unique string of developer and Y = a unique number for this app
set(VITA_TITLEID  "ABBN66666")
# Optional version string to show in LiveArea's more info screen
set(VITA_VERSION  "01.00")

## Flags and includes for building
# Note that we make sure not to overwrite previous flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# Optional. You can specify more param.sfo flags this way.
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

# Add any additional include paths here
include_directories(
  ../common # This is for debugScreenPrintf(), you shouldn't need it in your projects
)

# Add any additional library paths here
# ${CMAKE_CURRENT_BINARY_DIR} lets you use any library currently being built
link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

## Build and link
# Add all the files needed to compile here
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/game.cpp
)

# Library to link to (drop the -l prefix). This will mostly be stubs.
target_link_libraries(${PROJECT_NAME}
  SceLibKernel_stub
  vita2d
  SceDisplay_stub
  SceGxm_stub
  SceSysmodule_stub
  SceAppMgr_stub
  SceCommonDialog_stub
  ScePgf_stub
  ScePvf_stub
  SceCtrl_stub
  SceThreadmgrForDriver_stub
  png
  z
)

## Create Vita files
vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
# The FILE directive lets you add additional files to the VPK, the syntax is
# FILE src_path dst_path_in_vpk. In this case, we add the LiveArea paths.
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  #FILE sce_sys/icon.png sce_sys/icon0.png
  FILE assets/logo.png assets/logo.png
  FILE assets/pacmanR.png assets/pacmanR.png
  FILE assets/pacmanL.png assets/pacmanL.png
  FILE assets/pacmanU.png assets/pacmanU.png
  FILE assets/pacmanD.png assets/pacmanD.png

  FILE assets/bGhostD.png assets/bGhostD.png
  FILE assets/bGhostL.png assets/bGhostL.png
  FILE assets/bGhostR.png assets/bGhostR.png
  FILE assets/bGhostU.png assets/bGhostU.png

  FILE assets/oGhostD.png assets/oGhostD.png
  FILE assets/oGhostL.png assets/oGhostL.png
  FILE assets/oGhostR.png assets/oGhostR.png
  FILE assets/oGhostU.png assets/oGhostU.png

  FILE assets/pGhostD.png assets/pGhostD.png
  FILE assets/pGhostL.png assets/pGhostL.png
  FILE assets/pGhostR.png assets/pGhostR.png
  FILE assets/pGhostU.png assets/pGhostU.png

  FILE assets/rGhostD.png assets/rGhostD.png
  FILE assets/rGhostL.png assets/rGhostL.png
  FILE assets/rGhostR.png assets/rGhostR.png
  FILE assets/rGhostU.png assets/rGhostU.png

  FILE assets/redHeart.png assets/redHeart.png
  FILE assets/grayHeart.png assets/grayHeart.png
)
