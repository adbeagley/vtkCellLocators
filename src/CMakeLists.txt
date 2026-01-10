file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS *.cpp *.c *.cxx)
file(GLOB_RECURSE INC_FILES CONFIGURE_DEPENDS *.h */*.h)

cmake_print_variables(SRC_FILES)
cmake_print_variables(INC_FILES)
vtk_module_add_module(CellLocators::CellLocators SOURCES ${SRC_FILES} HEADERS ${INC_FILES})

# set(classes StaticCellLocator CellLocator OBBTree)

# vtk_module_add_module(CellLocators::CellLocators CLASSES ${classes})
