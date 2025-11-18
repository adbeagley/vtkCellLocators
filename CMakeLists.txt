# Require CMake 3.15+ (matching scikit-build-core) Use new versions of all
# policies up to CMake 4.0
cmake_minimum_required(VERSION 3.15...3.25)

# Scikit-build-core sets these values based on pyproject.toml
project(
    ${SKBUILD_PROJECT_NAME}
    VERSION ${SKBUILD_PROJECT_VERSION}
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePrintHelpers)

# Only overwrite it if it set to default
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" CACHE PATH)
endif()
cmake_print_variables(CMAKE_INSTALL_PREFIX)

# TODO: review if these lines are even needed?
# https://scikit-build-core.readthedocs.io/en/latest/guide/cmakelists.html
# You can access all of the possible output directories, regardless of configuration, with the variables:

# - ${SKBUILD_PLATLIB_DIR}: The original platlib directory. Anything here goes directly to site-packages when a wheel is installed.

# - ${SKBUILD_DATA_DIR}: The data directory. Anything here goes to the root of the environment when a wheel is installed (use with care).

# - ${SKBUILD_HEADERS_DIR}: The header directory. Anything in here gets installed to Python’s header directory.

# - ${SKBUILD_SCRIPTS_DIR}: The scripts directory. Anything placed in here will go to bin (Unix) or Scripts (Windows).

# - ${SKBUILD_METADATA_DIR}: The dist-info directory. Licenses go in the licenses subdirectory. _Note that CMake is not run in the prepare_metadata_\* hooks, so anything written to this directory will only be present when writing wheels._

# - ${SKBUILD_NULL_DIR}: Anything installed here will not be placed in the wheel.

# Windows export symbols.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Include customized FindPackage scripts
# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# Set PIC
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Build external dependencies
# cmake_policy(SET CMP0074 NEW)
list(APPEND VTK_COMPONENTS
    vtksys
    CommonCore
    CommonDataModel
    FiltersGeneral
    FiltersCore
    FiltersGeometry
    WrappingPythonCore
)

add_subdirectory(extern)

# Include and build source
add_subdirectory(src)
