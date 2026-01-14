# Require CMake 3.15+ (matching scikit-build-core) Use new versions of all
# policies up to CMake 4.0
cmake_minimum_required(VERSION 3.15)

# Scikit-build-core sets these values based on pyproject.toml
project(
    ${SKBUILD_PROJECT_NAME}
    VERSION ${SKBUILD_PROJECT_VERSION}
    LANGUAGES CXX
)

include(GNUInstallDirs)
include(CMakePrintHelpers)
include(CTest)

set(CMAKE_INSTALL_PREFIX ${SKBUILD_DATA_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PYTHON_NAME ${SKBUILD_PROJECT_NAME})

cmake_print_variables(CMAKE_INSTALL_PREFIX)
cmake_print_variables(CMAKE_BINARY_DIR)
cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)
cmake_print_variables(SRC_DIR)
# cmake_print_variables(SKBUILD_PLATLIB_DIR)
# cmake_print_variables(SKBUILD_HEADERS_DIR)
# cmake_print_variables(SKBUILD_DATA_DIR)
# cmake_print_variables(SKBUILD_METADATA_DIR)

# TODO: review if these lines are even needed?
# https://scikit-build-core.readthedocs.io/en/latest/guide/cmakelists.html
# You can access all of the possible output directories, regardless of configuration, with the variables:

# - ${SKBUILD_PLATLIB_DIR}: The original platlib directory. Anything here goes directly to site-packages when a wheel is installed.

# - ${SKBUILD_DATA_DIR}: The data directory. Anything here goes to the root of the environment when a wheel is installed (use with care).

# - ${SKBUILD_HEADERS_DIR}: The header directory. Anything in here gets installed to Python’s header directory.

# - ${SKBUILD_SCRIPTS_DIR}: The scripts directory. Anything placed in here will go to bin (Unix) or Scripts (Windows).

# - ${SKBUILD_METADATA_DIR}: The dist-info directory. Licenses go in the licenses subdirectory. _Note that CMake is not run in the prepare_metadata_\* hooks, so anything written to this directory will only be present when writing wheels._

# - ${SKBUILD_NULL_DIR}: Anything installed here will not be placed in the wheel.

# # Windows export symbols.
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# # Set PIC
# set(CMAKE_POSITION_INDEPENDENT_CODE ON)


find_package(VTK COMPONENTS CommonCore CommonDataModel FiltersModeling Python)
if(NOT VTK_FOUND)
    message("Skipping example: ${VTK_NOT_FOUND_MESSAGE}")
    return()
endif()

set(_shared_default ON)
get_target_property(_vtk_libtype VTK::CommonCore TYPE)
if(_vtk_libtype STREQUAL "STATIC_LIBRARY")
    set(_shared_default OFF)
endif()

option(BUILD_SHARED_LIBS "Build shared or static libraries" "${_shared_default}")

# First we scan the modules in our project to find out the dependency graph
# between them.
vtk_module_scan(
    # With only 1 module file, this is easier. With more,
    # `vtk_module_find_modules` would be preferred.
    MODULE_FILES "${SRC_DIR}/vtk.module"
    # Not building the only module we have is silly.
    REQUEST_MODULES CellLocators::CellLocators
    # Store the list of provided modules from this scan.
    PROVIDES_MODULES modules
    # Enable the tests for our modules.
    ENABLE_TESTS ON)

# vtk_module_python_default_destination(python_destination)
set(python_destination ".") # SKBUILD has set this correctly already
cmake_print_variables(python_destination)
cmake_print_variables(modules)


# Build the module we just scanned.
vtk_module_build(MODULES ${modules})

# Wrap it with Python.
vtk_module_wrap_python(
    MODULES ${modules}
    TARGET CellLocators::CellLocatorsPython
    WRAPPED_MODULES wrapping_modules
    INSTALL_EXPORT wrapping_export
    PYTHON_PACKAGE "${PYTHON_NAME}"
    MODULE_DESTINATION "${python_destination}"
    # This is required if INSTALL_HEADERS is ON.
    CMAKE_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PYTHON_NAME}Python"
    LIBRARY_DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    # Static Python modules are almost never wanted.
    BUILD_STATIC OFF
    BUILD_PYI_FILES ON # want type hinting
    # Do not install headers for Python modules. Enable this option
    # if you are supporting static python module. It will install a header
    # file `WrappablePython.h`, which defines a function
    # `void WrappablePythonLoad()` which will add all Python modules created
    # by this call to the imported module table.
    INSTALL_HEADERS OFF)

cmake_print_variables(wrapping_export)
cmake_print_variables(wrapping_modules)


# Create an `__init__.py` containing wrapped filters.
set(python_modules)
foreach(module ${modules})
    _vtk_module_get_module_property("${module}"
        PROPERTY "library_name"
        VARIABLE library_name)
    list(APPEND python_modules "'${library_name}'")
endforeach()

list(JOIN python_modules , python_modules_string)
configure_file(
    "${SRC_DIR}/__init__.py.in"
    "${CMAKE_BINARY_DIR}/${python_destination}/${PYTHON_NAME}/__init__.py"
    @ONLY)
install(
    FILES "${CMAKE_BINARY_DIR}/${python_destination}/${PYTHON_NAME}/__init__.py"
    DESTINATION "${python_destination}/${PYTHON_NAME}/")

# Create and add _build_path.py to support importing from
# build tree and generating pyi files, no need to install it though
configure_file(
    "${SRC_DIR}/_build_paths.py.in"
    "${CMAKE_BINARY_DIR}/${python_destination}/${PYTHON_NAME}/_build_paths.py"
    @ONLY)
