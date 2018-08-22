#
# raiigl project
# Under the Copyright (C) Christophe-Alexandre Sonntag (http://u4a.at)
# More information on : http://projects.u4a.at/library/rpi-cpp-automatism

# --- PROJECT ---
project(raiigl)
cmake_minimum_required(VERSION 3.2)
#
set(RAIIGL_VERSION_MAJOR 1)
set(RAIIGL_VERSION_MINOR 0)

#
##
#

# --- PROFILE ENVIRONNEMENT ---
if(CMAKE_COMPILER_IS_GNUCXX)                ## (GNU COMMAND)
  add_definitions("-Wall" "-pedantic")        # Toutes erreurs sauf :
  add_definitions("-Wno-unused-function" "-Wno-unknown-pragmas") #
  if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")   ## (not debug)
    add_compile_options("-fno-builtin")         ## Break __buildin function (so slowest)
    add_compile_options("-O3")                  ### Optimize
    set(CMAKE_EXE_LINKER_FLAGS "-s")            ### Strip binary (no work on debug)
  endif()
endif()

set(CMAKE_CXX_STANDARD 14)

#
##
#

## # --- SET CMAKE MODULES ---
## set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CMakeModules;${CMAKE_MODULE_PATH}")
## include("CMakeAutoSharedFilesCopier")


# --- LIB : OpenGL ---
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
link_directories(${OPENGL_DIRECTORIES})
link_libraries(${OPENGL_LIBRARIES})
add_definitions(${OPENGL_DEFINITIONS})

# --- LIB : GLEW ---
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_DIRECTORIES})
link_libraries(${GLEW_LIBRARIES})
add_definitions(${GLEW_DEFINITIONS})

# --- LIB : GLM ---
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
link_directories(${GLM_DIRECTORIES})
link_libraries(${GLM_LIBRARIES})
add_definitions(${GLM_DEFINITIONS})



#
##
#

# --- TARGETS PATH ---
set(HEADER_PATH "include")
set(HEADER_SUBPATH "${HEADER_PATH}/raiigl")
set(IPP_PATH "${HEADER_SUBPATH}/ipp")

# --- TARGETS FILES ---
file(GLOB_RECURSE TARGET_HEADER_FILES "${HEADER_PATH}/*.h" "${HEADER_PATH}/*.hpp")
file(GLOB_RECURSE TARGET_IPP_FILES "${IPP_PATH}/*.ipp")

# --- COMPILE OPTIONS ---
include_directories(${HEADER_PATH})

#
##
#

# --- BUILD OPTIONS  ---
SET(RAIIGL_BUILD_TOOLS ON CACHE BOOL "Build tools for RAIIGL library")
SET(RAIIGL_BUILD_EXAMPLES ON CACHE BOOL "Build examples for RAIIGL library")
SET(RAIIGL_BUILD_TESTS ON CACHE BOOL "Build tests for RAIIGL library")


#
##
#

add_library(${PROJECT_NAME} STATIC "just-hello.cpp" ${TARGET_HEADER_FILES} ${TARGET_IPP_FILES})

#
##
#

# --- INSTALL INCLUDE ---
install(DIRECTORY "${HEADER_PATH}/." DESTINATION "include")

#
##
#

## --- BUILDS TOOLS ---
#if(${RAIIGL_BUILD_TOOLS})
# add_subdirectory("tools/")
#endif()
#
## --- BUILDS EXAMPLES ---
#if(${RAIIGL_BUILD_EXAMPLES})
# add_subdirectory("examples/")
#endif()
#
## --- BUILDS TESTS ---
#if(${RAIIGL_BUILD_TESTS})
#    add_subdirectory("tests/")
#endif()

