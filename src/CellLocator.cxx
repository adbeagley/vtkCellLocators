#include "CellLocator.h"
#include "FindClosestPoints.h"
#include <vtkObjectFactory.h>
#include <vtkPoints.h>
#include <vtkIdList.h>
#include <vtkNew.h>
#include <vtkCell.h>
#include <vtkGenericCell.h>
#include <vtkCellArray.h>
#include <vtkIntArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkCellIterator.h>
#include <vtkDataSet.h>

// CellLocator
vtkStandardNewMacro(CellLocator);

CellLocator::CellLocator() = default;

CellLocator::~CellLocator() = default;

vtkSmartPointer<vtkPoints> CellLocator::FindClosestPoints(
    vtkPoints *points,
    vtkIdList *cell_ids,
    vtkIdList *sub_ids)
{
    return API::FindClosestPoints(this, points, cell_ids, sub_ids);
}
