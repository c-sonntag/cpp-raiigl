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
set(PROJECT_RAIIGL_STATIC "${PROJECT_NAME}_static")
set(PROJECT_RAIIGL_SHARED "${PROJECT_NAME}_shared")

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
set(CPP_PATH "src")
set(HEADER_PATH "include")
set(HEADER_SUBPATH "${HEADER_PATH}/raiigl")
set(IPP_PATH "${HEADER_SUBPATH}/ipp")

# --- TARGETS FILES ---
file(GLOB_RECURSE TARGET_HEADER_FILES "${HEADER_PATH}/*.h" "${HEADER_PATH}/*.hpp")
file(GLOB_RECURSE TARGET_IPP_FILES "${IPP_PATH}/*.ipp")
file(GLOB_RECURSE TARGET_CPP_FILES "${CPP_PATH}/*.c" "${CPP_PATH}/*.cpp")

# --- COMPILE OPTIONS ---
include_directories(${HEADER_PATH})

#
##
#

# --- BUILD OPTIONS : STATIC/SHARED ---
SET(RAIIGL_SHARED ON CACHE BOOL "Build shared RAIIGL library")
SET(RAIIGL_STATIC ON CACHE BOOL "Build static RAIIGL library")

# --- CHECK BUILD OPTIONS ---
if( (NOT ${RAIIGL_SHARED}) AND (NOT ${RAIIGL_STATIC}) )
  message(FATAL_ERROR, "\n\n   !! Require one of SHARED or STATIC for RAIIGL !! \n\n")
  set(RAIIGL_FOUND OFF)
  return()
endif()


#
##
#

# --- BUILD OPTIONS  ---
## set(RAIIGL_BUILD_TOOLS    ON CACHE BOOL "Build tools for RAIIGL library")
## set(RAIIGL_BUILD_TESTS    ON CACHE BOOL "Build tests for RAIIGL library")
set(RAIIGL_BUILD_EXAMPLES ON CACHE BOOL "Build examples for RAIIGL library")

# --- SUB BUILD LINKING ---
set(PROJECT_SUBPROJECT_HEADER_PATH "${CMAKE_CURRENT_LIST_DIR}/${HEADER_PATH}")
if(RAIIGL_STATIC)
  set(PROJECT_SUBPROJECT_LINKING ${PROJECT_RAIIGL_STATIC})
elseif(RAIIGL_SHARED)
  set(PROJECT_SUBPROJECT_LINKING ${PROJECT_RAIIGL_SHARED})
endif()

#
##
#

# --- BUILDS LIB TARGET STATIC ---
if(${RAIIGL_STATIC})

  # --- ---
  add_library(${PROJECT_RAIIGL_STATIC} STATIC ${TARGET_CPP_FILES} ${TARGET_HEADER_FILES})
  set_target_properties(${PROJECT_RAIIGL_STATIC} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

  # --- INSTALL LIB ---
  install(TARGETS ${PROJECT_RAIIGL_STATIC}
          LIBRARY DESTINATION "lib"
          ARCHIVE DESTINATION "lib")

endif()

# --- BUILDS LIB TARGET SHARED ---
if(${RAIIGL_SHARED})

  # --- ---
  add_library(${PROJECT_RAIIGL_SHARED} SHARED ${TARGET_CPP_FILES} ${TARGET_HEADER_FILES})
  set_target_properties(${PROJECT_RAIIGL_SHARED} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

  # --- INSTALL LIB ---
  install(TARGETS ${PROJECT_RAIIGL_SHARED}
          RUNTIME DESTINATION "bin"
          LIBRARY DESTINATION "lib"
          ARCHIVE DESTINATION "lib")

endif()

# --- INSTALL INCLUDE ---
install(DIRECTORY "${HEADER_PATH}/." DESTINATION "include")

#
## Subproject
#

set(PROJECT_RAIIGL_HEADER_PATH "${CMAKE_CURRENT_LIST_DIR}/${HEADER_PATH}")


#
##
#

# # --- BUILDS TOOLS  ---
# if(${RAIIGL_BUILD_TOOLS})
#   ##add_subdirectory("tools/")
# endif()

# # --- BUILDS EXAMPLES ---
# if(${RAIIGL_BUILD_EXAMPLES})
#  add_subdirectory("examples/")
# endif()

# # --- BUILDS TESTS ---
# if(${RAIIGL_BUILD_TESTS} AND EXISTS ${ERC_BINARY_PACKAGER})
#   add_subdirectory("tests/")
# endif()
