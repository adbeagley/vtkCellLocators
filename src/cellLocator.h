#include <vtkIdList.h>
#include <vtkNew.h>
#include <vtkCell.h>
#include <vtkDataSet.h>
#include <vtkCellArray.h>
#include <vtkShrinkFilter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkGeometryFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkExtractCells.h>
#include <vtkTriangleFilter.h>
#include <vtkCompositeDataProbeFilter.h>
#include <vtkIntArray.h>
#include <vtkDoubleArray.h>
#include <vtkCellCenters.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkIndent.h>
#include <vtkCellIterator.h>
#include <vtkKdTreePointLocator.h>
#include <vtkPolyDataNormals.h>
#include <vtkMultiObjectMassProperties.h>
#include <vtkCompositeDataProbeFilter.h>
#include <vtkAbstractCellLocator.h>
#include <vtkStaticCellLocator.h>
#include <vtkCellLocator.h>
#include <type_traits>
#include <regex>
#include "printer.h"

using vtkIdMap = std::map<vtkIdType, vtkSmartPointer<vtkIdList>>;
using stringVec = std::vector<std::string>;

class CellLocator
{

private:
    vtkSmartPointer<vtkAbstractCellLocator> locator;

public:
    // Constructor
    // template <typename T>
    CellLocator(vtkAbstractCellLocator *locator, vtkDataSet *source)
    {
        // static_assert(std::is_base_of<vtkAbstractCellLocator, T>::value);
        this->locator = vtkSmartPointer<vtkAbstractCellLocator>(locator);
        this->locator->SetDataSet(source);
        this->locator->BuildLocator();
    }

    vtkSmartPointer<vtkPoints> FindClosestPoints(vtkPoints *points)
    {
        double query_point[3];
        double closest_point[3];
        vtkIdType cell_id;
        int sub_id;
        double dist2;
        vtkNew<vtkGenericCell> cell;

        vtkNew<vtkPoints> out_pts;
        out_pts->SetNumberOfPoints(points->GetNumberOfPoints());

        for (vtkIdType i = 0; i < points->GetNumberOfPoints(); i++)
        {
            points->GetPoint(i, query_point);
            this->locator->FindClosestPoint(
                query_point,
                closest_point,
                cell,
                cell_id,
                sub_id,
                dist2);
            out_pts->SetPoint(i, closest_point);
        }
        return vtkSmartPointer<vtkPoints>(out_pts);
    }
};
