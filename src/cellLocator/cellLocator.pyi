"""

Python wrapper for vtkAbstractCellLocator to place for loop iteration over query points inside of C++ code
-----------------------

.. currentmodule:: cellLocator

.. autosummary::
   :toctree: _generate

   update
   get_output

"""

from __future__ import annotations
from vtkmodules.all import vtkAbstractCellLocator, vtkDataSet, vtkPoints

__all__: list[str] = ["CellLocator"]

class CellLocator:
    def __init__(self, arg0: vtkAbstractCellLocator, arg1: vtkDataSet) -> None: ...
    def find_closest_points(self, arg0: vtkPoints) -> vtkPoints:
        """
        Find closest points on surface.
        """

__version__: str = "0.0.1"
