# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ConfigTool_Pc_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ConfigTool_Pc_autogen.dir\\ParseCache.txt"
  "ConfigTool_Pc_autogen"
  )
endif()
