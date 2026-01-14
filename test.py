from vtkmodules import vtkDataSet

import vtkCellLocators

for x in dir(vtkCellLocators):
    print(x)

from vtkCellLocators import StaticCellLocator

print(StaticCellLocator)
print(dir(StaticCellLocator))
