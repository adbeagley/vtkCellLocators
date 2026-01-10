#include "OBBTree.h"
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

// OBBTree
vtkStandardNewMacro(OBBTree);

OBBTree::OBBTree() = default;

OBBTree::~OBBTree() = default;

vtkSmartPointer<vtkPoints> OBBTree::FindClosestPoints(
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
        this->FindClosestPoint(
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
