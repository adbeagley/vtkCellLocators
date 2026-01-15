// #ifndef FindClosestPoints_h
// #define FindClosestPoints_h

#pragma once
#include <vtkAbstractCellLocator.h>
#include <vtkPoints.h>
#include <vtkIdList.h>

namespace API
{
    vtkSmartPointer<vtkPoints> FindClosestPoints(
        vtkAbstractCellLocator *locator,
        vtkPoints *points,
        vtkIdList *cell_ids,
        vtkIdList *sub_ids);
}

// #endif
