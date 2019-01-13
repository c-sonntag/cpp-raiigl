#
## CMakeCustomModules Utils
##
## Need folowing arguments :
##   - LIB_NAME 
##   - LIB_INCLUDE_NAMES 
##   - LIB_IMPORT_NAMES 
##   - LIB_DEFINITONS 
##   - OUTPUT_TARGET_NAME
##
## To provide macro as LIB_IMPORTER to import :
##   - variables : 
##     - ${LIB_NAME}_POSSIBLE_PATH
##     - ${LIB_NAME}_INCLUDE_DIRS / ${LIB_NAME}_INCLUDE_DIR
##     - ${LIB_NAME}_LIBRARIES / ${LIB_NAME}_LIBRARY
##     - ${LIB_NAME}_DEFINITIONS
##     - ${LIB_NAME}_DIRECTORIES
##   - target : 
##     - ${OUTPUT_TARGET_NAME}_static 
##     - ${OUTPUT_TARGET_NAME}_shared
#

#  Include_Guards : This module is loaded multiple times. 
if(DEFINED __CMakeCustomModules_IMPORTED)
  return()
endif()

set(__CMakeCustomModules_DEBUG OFF)


#
##
#

  
macro(__LIB_IMPORTER_LIBRARIES_FINDER LIB_NAME FROM_IMPORT OUTPUT_LIBRARIES_PATH)

  if(__CMakeCustomModules_DEBUG)
    message(STATUS "__LIB_IMPORTER_LIBRARIES_FINDER for ${LIB_NAME} : ${FROM_IMPORT} ")
  endif()

  #
  ##
  set(${LIB_NAME}_LIBRARIES_NAMES "")
  foreach(import_name ${FROM_IMPORT})
    list(APPEND ${LIB_NAME}_LIBRARIES_NAMES "${import_name}")
    if(${${LIB_NAME}_STATIC})
      list(APPEND ${LIB_NAME}_LIBRARIES_NAMES "${import_name}static" "${import_name}_static")
    elseif(${${LIB_NAME}_SHARED})
      list(APPEND ${LIB_NAME}_LIBRARIES_NAMES "${import_name}shared" "${import_name}_shared")
    endif()
  endforeach()
  
  #
  set(${LIB_NAME}_LIBRARIES_NAMES_COMBINED "${FROM_IMPORT}")
  foreach(import_names ${${LIB_NAME}_LIBRARIES_NAMES})
    foreach(lib_suffix ${${LIB_NAME}_LIBRARIES_SUFFIX})
      foreach(lib_prefix ${${LIB_NAME}_LIBRARIES_PREFFIX})
        list(APPEND ${LIB_NAME}_LIBRARIES_NAMES_COMBINED 
          "${lib_prefix}${import_names}${lib_suffix}" 
        )
      endforeach()
    endforeach()    
  endforeach()
  
  #
  ##
  #set(${OUTPUT_LIBRARIES_PATH} "")
  #if(NOT DEFINED ${LIB_NAME}_LIBRARIES_SEARCH)
  if(${${LIB_NAME}_STATIC})
    #if(NOT ${LIB_NAME}_LIBRARIES_STATIC_FOUND)
      #set(${LIB_NAME}_LIBRARIES_STATIC_FOUND)
      foreach(import_lib ${${LIB_NAME}_LIBRARIES_NAMES_COMBINED})
        string(SHA1 import_lib_HASH "${import_lib}")
        find_library(
          ${LIB_NAME}_LIBRARIES_STATIC_${import_lib_HASH}_FOUND
          NAMES ${import_lib}
          PATHS ${${LIB_NAME}_POSSIBLE_PATH}
          PATH_SUFFIXES "lib/"
        )
        if(${LIB_NAME}_LIBRARIES_STATIC_${import_lib_HASH}_FOUND)
          #LIST(APPEND ${LIB_NAME}_LIBRARIES_STATIC_FOUND "${${LIB_NAME}_LIBRARIES_STATIC_${import_lib_HASH}_FOUND}")
          LIST(APPEND ${OUTPUT_LIBRARIES_PATH} "${${LIB_NAME}_LIBRARIES_STATIC_${import_lib_HASH}_FOUND}")
        endif()
      endforeach()
    #endif()
  elseif(${${LIB_NAME}_SHARED})
    #if(NOT ${LIB_NAME}_LIBRARIES_SHARED_FOUND)
      #set(${LIB_NAME}_LIBRARIES_SHARED_FOUND)
      foreach(import_lib ${${LIB_NAME}_LIBRARIES_NAMES_COMBINED})
        string(SHA1 import_lib_HASH "${import_lib}")
        find_library(
          ${LIB_NAME}_LIBRARIES_SHARED_${import_lib_HASH}_FOUND
          NAMES ${import_lib}
          PATHS ${${LIB_NAME}_POSSIBLE_PATH}
          PATH_SUFFIXES "lib/"
        )
        if(${LIB_NAME}_LIBRARIES_SHARED_${import_lib_HASH}_FOUND)
          #LIST(APPEND ${LIB_NAME}_LIBRARIES_SHARED_FOUND "${${LIB_NAME}_LIBRARIES_SHARED_${import_lib_HASH}_FOUND}")
          LIST(APPEND ${OUTPUT_LIBRARIES_PATH} "${${LIB_NAME}_LIBRARIES_SHARED_${import_lib_HASH}_FOUND}")
        endif()
      endforeach()
    #endif()
  endif()
  
  if(__CMakeCustomModules_DEBUG)
    message(STATUS "${LIB_NAME}_LIBRARIES_NAMES_COMBINED : ${${LIB_NAME}_LIBRARIES_NAMES_COMBINED}")
    message(STATUS "${OUTPUT_LIBRARIES_PATH} : ${${OUTPUT_LIBRARIES_PATH}}")
  endif()
    
  #  set(${LIB_NAME}_LIBRARIES_SEARCH ON)
  #endif()
  
endmacro()

#
##
#

macro(__LIB_IMPORTER_COMPONENT_PARSER LIB_NAME user_component_name OUTPUT_LIBRARIES_PATH)

  set(${LIB_NAME}__COMPONENT_PARSER_FOUND OFF)
  foreach(valid_component_name ${${LIB_NAME}_VARGS_COMPONENTS})
    if("${valid_component_name}" STREQUAL "${user_component_name}")
      __LIB_IMPORTER_LIBRARIES_FINDER(${LIB_NAME} "${valid_component_name}" ${OUTPUT_LIBRARIES_PATH})
      set(${LIB_NAME}__COMPONENT_PARSER_FOUND ON)
      break()
    endif()
  endforeach()
  if(NOT ${LIB_NAME}__COMPONENT_PARSER_FOUND)
    message(WARNING "\n\n \
      Unknown components '${user_component_name}' into command : \n\
        find_package(${LIB_NAME} COMPONENTS ... ) \n\
      \n\n" )
  endif()
endmacro()


#
##
#
macro(LIB_IMPORTER LIB_NAME LIB_INCLUDE_NAMES LIB_IMPORT_NAMES LIB_DEFINITONS OUTPUT_TARGET_NAME)
  
    
  if(__CMakeCustomModules_DEBUG)
    message(STATUS "LIB_NAME           : ${LIB_NAME}")
    message(STATUS "LIB_INCLUDE_NAMES  : ${LIB_INCLUDE_NAMES}")
    message(STATUS "LIB_IMPORT_NAMES   : ${LIB_IMPORT_NAMES}")
    message(STATUS "LIB_DEFINITONS     : ${LIB_DEFINITONS}")
    message(STATUS "OUTPUT_TARGET_NAME : ${OUTPUT_TARGET_NAME}")
  endif()
  
  #
  ## Otionnal Values
  set(LIB_IMPORTER_Options NO_TARGET FORCE_MSVC_LIB FORCE_SHARED)
  set(LIB_IMPORTER_OneValueArgs)
  set(LIB_IMPORTER_MultiValueArgs COMPONENTS PATH_SUFFIXES)
  cmake_parse_arguments(
    ${LIB_NAME}_VARGS 
    "${LIB_IMPORTER_Options}" 
    "${LIB_IMPORTER_OneValueArgs}" 
    "${LIB_IMPORTER_MultiValueArgs}" 
    ${ARGN} 
  )
  
  #
  ##
  if(${LIB_NAME}_VARGS_FORCE_SHARED)
    set(${LIB_NAME}_SHARED ON)
    set(${LIB_NAME}_STATIC OFF)
  endif()
    
  #
  ##
  if( 
    ( (NOT ${LIB_NAME}_SHARED) AND (NOT ${LIB_NAME}_STATIC) ) OR
    ( (${LIB_NAME}_SHARED) AND (${LIB_NAME}_STATIC) ) OR
    ( (NOT DEFINED ${LIB_NAME}_SHARED) AND (NOT ${LIB_NAME}_STATIC) ) OR
    ( (NOT DEFINED ${LIB_NAME}_STATIC) AND (NOT ${LIB_NAME}_SHARED) )
  )
    message(SEND_ERROR
      "\n\n"
      "   !! Require one of SHARED or STATIC setting for ${LIB_NAME} !! \n"
      "   !! You can FIX IT by ${LIB_NAME}_STATIC/${LIB_NAME}_SHARED variables !! \n"
      "   !! Configure It By CMake DEFINITON !! \n"
      "   !! Actual ${LIB_NAME}_SHARED=${${LIB_NAME}_SHARED} and ${LIB_NAME}_STATIC=${${LIB_NAME}_STATIC} !! \n"
      "\n"
    )
    set(${LIB_NAME}_FOUND OFF)
    return()
  endif()
  if(${LIB_NAME}_STATIC)
    set(${LIB_NAME}_LIB_TYPE STATIC)
  elseif(${LIB_NAME}_SHARED)
    set(${LIB_NAME}_LIB_TYPE SHARED)
  endif()
  
  if(__CMakeCustomModules_DEBUG)
    message(STATUS "${LIB_NAME}_LIB_TYPE  : ${${LIB_NAME}_LIB_TYPE}")
    message(STATUS "${LIB_NAME}_VARGS_NO_TARGET  : ${${LIB_NAME}_VARGS_NO_TARGET}")
    message(STATUS "${LIB_NAME}_VARGS_COMPONENTS  : ${${LIB_NAME}_VARGS_COMPONENTS}")
    if (${LIB_NAME}_FIND_COMPONENTS)
      message(STATUS "${LIB_NAME}_FIND_COMPONENTS  : ${${LIB_NAME}_FIND_COMPONENTS}")
    endif()
  endif()
  
  #
  ##
  if( 
    (NOT ${LIB_NAME}_FIND_COMPONENTS) 
    AND (NOT LIB_IMPORT_NAMES)
    AND ${LIB_NAME}_VARGS_COMPONENTS
  )  
    message(SEND_ERROR "\n\n \
      Need component(s) from find_package(${LIB_NAME} ...) \n\
        Exemple for all components : find_package(${LIB_NAME} COMPONENTS ${LIB_NAME}_VARGS_COMPONENTS REQUIRED) \n\
      \n\n"
    )
    set(${LIB_NAME}_FOUND OFF)
    return()
  endif()  
  
  #
  ## TODO INSERT COMPONENTS TAGET _FOUND / _EXIST VALIDITY
  #
  
  #
  ##
  if(DEFINED ${LIB_NAME}_${${LIB_NAME}_LIB_TYPE}_FOUND})
    return()
  endif()
  
  #
  ##
  set(${LIB_NAME}_POSSIBLE_PATH
    "${${LIB_NAME}_DIR}"
    "${${LIB_NAME}_SUFFIX}"
    "${${LIB_NAME}_ROOT}"
  #  "${CMAKE_SOURCE_DIR}/external/${LIB_NAME}"
  #  "${CMAKE_SOURCE_DIR}/thirdparty/${LIB_NAME}"
  #  "${CMAKE_SOURCE_DIR}/third-party/${LIB_NAME}"
  )
  
  #
  ##
  find_path(
    ${LIB_NAME}_INCLUDE_DIRS_FOUND
    NAMES ${LIB_INCLUDE_NAMES}
    PATHS ${${LIB_NAME}_POSSIBLE_PATH}
    PATH_SUFFIXES "include/" "inc/" ${${LIB_NAME}_VARGS_PATH_SUFFIXES}
  )
  if(${LIB_NAME}_INCLUDE_DIRS_FOUND)
    set(${LIB_NAME}_INCLUDE_DIRS ${${LIB_NAME}_INCLUDE_DIRS_FOUND} "${${LIB_NAME}_INCLUDE_DIRS}")
    set(${LIB_NAME}_INCLUDE_DIR  ${${LIB_NAME}_INCLUDE_DIRS_FOUND} "${${LIB_NAME}_INCLUDE_DIR}")
  endif()
  
  #
  ##
  if(${LIB_NAME}_VARGS_FORCE_MSVC_LIB)
    set(OLD_CMAKE_STATIC_LIBRARY_SUFFIX ${CMAKE_STATIC_LIBRARY_SUFFIX})
    set(OLD_CMAKE_SHARED_LIBRARY_SUFFIX ${CMAKE_SHARED_LIBRARY_SUFFIX})
    set(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".lib")
  endif()

  #
  ## PREPARE : SUFFIX & PREFFIX
  set(${LIB_NAME}_LIBRARIES_SUFFIX "") 
  set(${LIB_NAME}_LIBRARIES_PREFFIX "") 
  if(${${LIB_NAME}_STATIC})
    list(APPEND ${LIB_NAME}_LIBRARIES_SUFFIX "${CMAKE_STATIC_LIBRARY_SUFFIX}")
    list(APPEND ${LIB_NAME}_LIBRARIES_PREFFIX "${CMAKE_STATIC_LIBRARY_PREFFIX}")
  elseif(${${LIB_NAME}_SHARED})
    list(APPEND ${LIB_NAME}_LIBRARIES_SUFFIX "${CMAKE_SHARED_LIBRARY_SUFFIX}")
    list(APPEND ${LIB_NAME}_LIBRARIES_PREFFIX "${CMAKE_SHARED_LIBRARY_PREFFIX}")
    IF (WIN32)
      list(APPEND ${LIB_NAME}_LIBRARIES_SUFFIX "dll")
    endif()
  endif()
  list(APPEND ${LIB_NAME}_LIBRARIES_PREFFIX "lib")
  #
  if(__CMakeCustomModules_DEBUG)
     message(STATUS "${LIB_NAME}_LIBRARIES_SUFFIX  : ${${LIB_NAME}_LIBRARIES_SUFFIX}")
     message(STATUS "${LIB_NAME}_LIBRARIES_PREFFIX : ${${LIB_NAME}_LIBRARIES_PREFFIX}")
  endif()

  #
  ##
  if(${LIB_NAME}_VARGS_FORCE_MSVC_LIB)
    set(CMAKE_STATIC_LIBRARY_SUFFIX ${OLD_CMAKE_STATIC_LIBRARY_SUFFIX})
    set(CMAKE_SHARED_LIBRARY_SUFFIX ${OLD_CMAKE_SHARED_LIBRARY_SUFFIX})
  endif()

  
  #
  ##
  set(${LIB_NAME}_LIBRARIES "")
  #
  if(NOT "${LIB_IMPORT_NAMES}" STREQUAL "")
    __LIB_IMPORTER_LIBRARIES_FINDER(${LIB_NAME} "${LIB_IMPORT_NAMES}" ${LIB_NAME}_LIBRARIES)
  endif()
  #
  if(${LIB_NAME}_VARGS_COMPONENTS AND ${LIB_NAME}_FIND_COMPONENTS)
    foreach(user_component_name ${${LIB_NAME}_FIND_COMPONENTS})
      __LIB_IMPORTER_COMPONENT_PARSER(${LIB_NAME} ${user_component_name} ${LIB_NAME}_LIBRARIES)
    endforeach()
  endif()
  #
  set(${LIB_NAME}_LIBRARY  ${${LIB_NAME}_LIBRARIES})
  
  #
  ##
  set(${LIB_NAME}_DEFINITIONS ${LIB_DEFINITONS})
  set(${LIB_NAME}_DIRECTORIES "")
  set(${LIB_NAME}_LOCATION "")

  #
  ##
  if(__CMakeCustomModules_DEBUG)
    message(STATUS "${LIB_NAME}_POSSIBLE_PATH : ${${LIB_NAME}_POSSIBLE_PATH}")
    message(STATUS "${LIB_NAME}_INCLUDE_DIRS  : ${${LIB_NAME}_INCLUDE_DIRS}")
    message(STATUS "${LIB_NAME}_LIBRARIES     : ${${LIB_NAME}_LIBRARIES}")
    message(STATUS "${LIB_NAME}_LIBRARY       : ${${LIB_NAME}_LIBRARY}")
  endif()

  #
  ##
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(${LIB_NAME} REQUIRED_VARS "${LIB_NAME}_LIBRARIES" "${LIB_NAME}_INCLUDE_DIRS")

  #
  ##
  if(${LIB_NAME}_INCLUDE_DIRS_FOUND)
    foreach(possible_path ${${LIB_NAME}_POSSIBLE_PATH})
      string(FIND ${LIB_NAME}_INCLUDE_DIRS_FOUND possible_path position_find_path)
      if(position_find_path)
        set(${LIB_NAME}_LOCATION "${possible_path}")
        break()
      endif()
    endforeach()
  endif()
  
  #
  ##
  if(__CMakeCustomModules_DEBUG)
    message(STATUS "${LIB_NAME}_LOCATION : ${${LIB_NAME}_LOCATION}")
  endif()
  
  #
  ## TODO INSERT COMPONENTS TAGET VALIDITY
  #
  
  #
  ##  
  if(NOT ${LIB_NAME}_VARGS_NO_TARGET)
    if(${${LIB_NAME}_STATIC})
      if(NOT TARGET ${OUTPUT_TARGET_NAME}_static)
      
        if(__CMakeCustomModules_DEBUG)
          message(STATUS "NEW TARGET : ${OUTPUT_TARGET_NAME}_static")
        endif()
    
        add_library(${OUTPUT_TARGET_NAME}_static STATIC IMPORTED)
        set_target_properties(${OUTPUT_TARGET_NAME}_static PROPERTIES
          IMPORTED_LOCATION             "${${LIB_NAME}_LOCATION}"
          INTERFACE_LINK_LIBRARIES      "${${LIB_NAME}_LIBRARIES}"
          INTERFACE_COMPILE_DEFINITIONS "${${LIB_NAME}_DEFINITIONS}"
          INTERFACE_INCLUDE_DIRECTORIES "${${LIB_NAME}_INCLUDE_DIR}"
          INTERFACE_LINK_DIRECTORIES    "${${LIB_NAME}_DIRECTORIES}"
        )
      endif()
    elseif(${${LIB_NAME}_SHARED})
      if(NOT TARGET ${OUTPUT_TARGET_NAME}_shared)
      
        if(__CMakeCustomModules_DEBUG)
          message(STATUS "NEW TARGET : ${OUTPUT_TARGET_NAME}_shared")
        endif()
      
        add_library(${OUTPUT_TARGET_NAME}_shared SHARED IMPORTED)
        set_target_properties(${OUTPUT_TARGET_NAME}_shared PROPERTIES
          IMPORTED_LOCATION             "${${LIB_NAME}_LOCATION}"
          INTERFACE_LINK_LIBRARIES      "${${LIB_NAME}_LIBRARIES}"
          INTERFACE_COMPILE_DEFINITIONS "${${LIB_NAME}_DEFINITIONS}"
          INTERFACE_INCLUDE_DIRECTORIES "${${LIB_NAME}_INCLUDE_DIR}"
          INTERFACE_LINK_DIRECTORIES    "${${LIB_NAME}_DIRECTORIES}"
        )
      endif()
    endif()
  endif()
  
  set(${LIB_NAME}_${${LIB_NAME}_LIB_TYPE}_FOUND ON)
  
  if(__CMakeCustomModules_DEBUG)
    message(STATUS "  ")
    message(STATUS "  ")
  endif()
  
endmacro()

set(__CMakeCustomModules_IMPORTED ON)


