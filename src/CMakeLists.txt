# Enumerate source files
# CONFIGURE_DEPENDS: CMake will rerun GLOB to check for changes when building
# even if CMakeLists.txt have not changed
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS *.cpp *.c)
file(GLOB_RECURSE INC_FILES CONFIGURE_DEPENDS *.h */*.h)

macro(get_parent path num out_path)
  # create tmp path and iteratively get parent
  cmake_path(SET tmp_path ${path})
  math(EXPR loop_num ${num}-1)
  foreach(i RANGE ${loop_num})
    cmake_path(GET tmp_path PARENT_PATH tmp_path)
  endforeach()

  # set output to parent
  cmake_path(SET ${out_path} NORMALIZE ${tmp_path})
  unset(tmp_path)
  unset(loop_num)
endmacro()

macro(path_ends_with path suffix)
  get_filename_component(filename ${path} NAME)
  if(${filename} STREQUAL ${suffix})
    set(ENDS_WITH_${suffix} true)
  else()
    set(ENDS_WITH_${suffix} false)
  endif()
  unset(filename)
endmacro()

macro(get_pip_overlay_path out_var)
  foreach(path ${CMAKE_PREFIX_PATH})
    if(NOT IS_ABSOLUTE ${path} OR NOT IS_DIRECTORY ${path})
      continue()
    endif()

    path_ends_with(${path} "site-packages")
    if(NOT ENDS_WITH_site-packages)
      continue()
    endif()
    unset(ENDS_WITH_site-packages)

    get_parent(${path} 2 parent_path)
    path_ends_with(${parent_path} "overlay")
    if(NOT ENDS_WITH_overlay)
      continue()
    endif()
    unset(ENDS_WITH_overlay)

    list(APPEND ${out_var} ${parent_path})
  endforeach()

  if(DEFINED ${out_var})
    set(PIP_OVERLAY_FOUND true)
  else()
    set(PIP_OVERLAY_FOUND false)
  endif()
endmacro()


macro(get_pip_packages_path out_var)
  foreach(path ${CMAKE_PREFIX_PATH})
    if(NOT IS_ABSOLUTE ${path} OR NOT IS_DIRECTORY ${path})
      continue()
    endif()

    path_ends_with(${path} "site-packages")
    if(NOT ENDS_WITH_site-packages)
      continue()
    endif()
    unset(ENDS_WITH_site-packages)

    get_parent(${path} 2 parent_path)
    path_ends_with(${parent_path} "overlay")
    if(NOT ENDS_WITH_overlay)
      continue()
    endif()
    unset(ENDS_WITH_overlay)

    cmake_path(SET ${out_var} NORMALIZE ${path})
    break()
  endforeach()

  if(DEFINED ${out_var})
    set(PIP_PACKAGES_FOUND true)
  else()
    set(PIP_PACKAGES_FOUND false)
  endif()
endmacro()

# NOTE: PYBIND11 was added via extern CMakeLists.txt
if(NOT pybind11_FOUND)
  message("Did not find pybind11!")
endif()

# Add a library using pybind11's tooling
pybind11_add_module(${SKBUILD_PROJECT_NAME} ${SRC_FILES} ${INC_FILES})

# This is passing in the version as a define just as an example
target_compile_definitions(
  ${SKBUILD_PROJECT_NAME} PRIVATE VERSION_INFO=${PROJECT_VERSION}
)

message("${VTK_LIBRARIES}")
if(NOT DEFINED VTK_LIBRARIES)
  message(SEND_ERROR "VTK_LIBRARIES is not defined!")
endif()

# link to required VTK and Manifold libraries
target_link_libraries(${SKBUILD_PROJECT_NAME}
  PRIVATE ${VTK_LIBRARIES}
)

# responsible for triggering static code construction required
# for some VTK classes. (Not needed since builing from source)
vtk_module_autoinit(TARGETS ${SKBUILD_PROJECT_NAME} MODULES ${VTK_LIBRARIES})


cmake_print_variables(CMAKE_INSTALL_PREFIX)
# The install directory relative to the output (wheel) directory
install(TARGETS ${SKBUILD_PROJECT_NAME} DESTINATION ${SKBUILD_PROJECT_NAME})

# copy into separate install dir post-build
# add_custom_command(TARGET ${SKBUILD_PROJECT_NAME}
#   POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
#     "${SITE_PACKAGES_INSTALL_DIR}"
#     "${LOCAL_INSTALL_DIR}"
#   COMMENT "Copying data"
# )

# copy into separate install dir
# add_custom_target(
#   copy_data
# 	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
#     "${SITE_PACKAGES_INSTALL_DIR}"
#     "${LOCAL_INSTALL_DIR}"
#   COMMENT "Copying data"
# )
# add_dependencies(${SKBUILD_PROJECT_NAME} copy_data)
