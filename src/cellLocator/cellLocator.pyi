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
from vtkmodules.all import vtkAbstractCellLocator, vtkIdList, vtkDataSet, vtkPoints

__all__: list[str] = ["CellLocator"]

class CellLocator:
    def __init__(self, locator: vtkAbstractCellLocator, source: vtkDataSet) -> None: ...
    def find_closest_points(
        self,
        points: vtkPoints,
        cell_ids: vtkIdList | None = None,
        sub_ids: vtkIdList | None = None,
    ) -> vtkPoints:
        """
        Find closest points on surface.
        """

__version__: str = "0.0.1"
