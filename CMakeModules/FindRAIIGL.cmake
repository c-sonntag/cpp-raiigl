#
## Import lib ZLIB with CMakeCustomModules Utils
#

#
##
include("${CMAKE_CURRENT_LIST_DIR}/CMakeCustomModules.cmake")


#
##
LIB_IMPORTER(
  RAIIGL          # LIB_NAME
  "raiigl/"       # LIB_INCLUDE_NAMES
  "raiigl"        # LIB_IMPORT_NAMES
  ""              # LIB_DEFINITONS 
  raiigl          # OUTPUT_TARGET_NAME
)








