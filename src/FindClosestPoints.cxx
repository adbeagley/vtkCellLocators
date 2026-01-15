// #ifndef FindClosestPoints_h
// #define FindClosestPoints_h

#pragma once

#include "FindClosestPoints.h"
#include <vtkSmartPointer.h>
#include <vtkNew.h>
#include <vtkGenericCell.h>

namespace API
{
    vtkSmartPointer<vtkPoints> FindClosestPoints(
        vtkAbstractCellLocator *locator,
        vtkPoints *points,
        vtkIdList *cell_ids,
        vtkIdList *sub_ids)
    {
        double query_point[3];
        double closest_point[3];
        vtkIdType cell_id;
        int sub_id;
        double dist2;
        vtkNew<vtkGenericCell> cell;

        bool return_cell_ids = cell_ids != nullptr;
        bool return_sub_ids = sub_ids != nullptr;

        if (return_cell_ids)
        {
            cell_ids->SetNumberOfIds(points->GetNumberOfPoints());
        }
        if (return_sub_ids)
        {
            sub_ids->SetNumberOfIds(points->GetNumberOfPoints());
        }

        vtkNew<vtkPoints> out_pts;
        out_pts->SetNumberOfPoints(points->GetNumberOfPoints());

        for (vtkIdType i = 0; i < points->GetNumberOfPoints(); i++)
        {
            points->GetPoint(i, query_point);
            locator->FindClosestPoint(
                query_point,
                closest_point,
                cell,
                cell_id,
                sub_id,
                dist2);
            out_pts->SetPoint(i, closest_point);
            if (return_cell_ids)
            {
                cell_ids->SetId(i, cell_id);
            }
            if (return_sub_ids)
            {
                sub_ids->SetId(i, sub_id);
            }
        }

        return vtkSmartPointer<vtkPoints>(out_pts);
    }
}

// #endif
