#include <pybind11/pybind11.h>
#include "../extern/PybindVTKTypeCaster.h"
#include "cellLocator.h" // grab local file

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;
using rvp = py::return_value_policy;

PYBIND11_MODULE(cellLocator, m)
{
    m.doc() = R"pbdoc(
        Python wrapper for vtkAbstractCellLocator to place for loop iteration over query points inside of C++ code
        -----------------------

        .. currentmodule:: cellLocator

        .. autosummary::
           :toctree: _generate

           find_closest_points
    )pbdoc";
    py::class_<CellLocator, py::smart_holder>(
        m, "CellLocator")
        .def(py::init<vtkAbstractCellLocator *, vtkDataSet *>())
        .def("find_closest_points", &CellLocator::FindClosestPoints, R"pbdoc(
                Find closest points on surface.
            )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
