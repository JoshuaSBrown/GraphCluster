
macro(CHECK_CXX_LIBRARY_EXISTS LIBRARY FUNCTION LOCATION VARIABLE)
  if(NOT DEFINED "${VARIABLE}")
    set(MACRO_CHECK_LIBRARY_EXISTS_DEFINITION
      "-DCHECK_FUNCTION_EXISTS=${FUNCTION} ${CMAKE_REQUIRED_FLAGS}")
    if(NOT CMAKE_REQUIRED_QUIET)
      message(STATUS "Looking for c++ ${FUNCTION} in ${LIBRARY}")
    endif()
    set(CHECK_LIBRARY_EXISTS_LIBRARIES ${LIBRARY})
    if(CMAKE_REQUIRED_LIBRARIES)
      set(CHECK_LIBRARY_EXISTS_LIBRARIES
        ${CHECK_LIBRARY_EXISTS_LIBRARIES} ${CMAKE_REQUIRED_LIBRARIES})
    endif()
    try_compile(${VARIABLE}
      ${CMAKE_BINARY_DIR}
      ${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules/CheckFunctionExists.cpp
      COMPILE_DEFINITIONS ${CMAKE_REQUIRED_DEFINITIONS}
      LINK_LIBRARIES ${CHECK_LIBRARY_EXISTS_LIBRARIES}
      CMAKE_FLAGS
      -DCOMPILE_DEFINITIONS:STRING=${MACRO_CHECK_LIBRARY_EXISTS_DEFINITION}
      -DLINK_DIRECTORIES:STRING=${LOCATION}
      OUTPUT_VARIABLE OUTPUT)

    if(${VARIABLE})
      if(NOT CMAKE_REQUIRED_QUIET)
        message(STATUS "Looking for c++ ${FUNCTION} in ${LIBRARY} - found")
      endif()
      set(${VARIABLE} 1 CACHE INTERNAL "Have library ${LIBRARY}")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
        "Determining if the function ${FUNCTION} exists in the ${LIBRARY} "
        "passed with the following output:\n"
        "${OUTPUT}\n\n")
    else()
      if(NOT CMAKE_REQUIRED_QUIET)
        message(STATUS "Looking for c++ ${FUNCTION} in ${LIBRARY} - not found")
      endif()
      set(${VARIABLE} "" CACHE INTERNAL "Have library ${LIBRARY}")
      file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
        "Determining if the function ${FUNCTION} exists in the ${LIBRARY} "
        "failed with the following output:\n"
        "${OUTPUT}\n\n")
    endif()
  endif()
endmacro()
