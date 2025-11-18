include(ExternalProject) # allow building sub_directory projects
include(CMakePrintHelpers)

# store current project name and prefix path
set(CURRENT_PROJECT_NAME ${CMAKE_PROJECT_NAME})
set(CURRENT_PREFIX_PATH ${CMAKE_PREFIX_PATH})

# Find vtk before searching for others
message(CHECK_START "Finding VTK")
find_package(VTK CONFIG COMPONENTS ${VTK_COMPONENTS} GLOBAL REQUIRED)
if(NOT VTK_FOUND)
    message(CHECK_FAIL "VTK not found")
else()
    message(CHECK_PASS "Found VTK")
    set(VTK_LIBRARIES ${VTK_LIBRARIES} PARENT_SCOPE)
    cmake_print_variables(VTK_LIBRARIES)
endif()

# set prefix path to only search local install
set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}")

# Find pybind11 and Python
set(PYBIND11_FINDPYTHON ON)
add_subdirectory(pybind11)
if(NOT pybind11_FOUND)
    message(SEND_ERROR "pybind11 not found!")
endif()

# reset prefix path to original value and then find VTK
set(CMAKE_PREFIX_PATH "${CURRENT_PREFIX_PATH}")
