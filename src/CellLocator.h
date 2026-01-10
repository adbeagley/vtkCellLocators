#ifndef CellLocator_h
#define CellLocator_h

#include "vtkCellLocatorsModule.h" // for export macro>
#include <vtkObject.h>
#include <vtkPoints.h>
#include <vtkIdList.h>
#include <vtkLocator.h>
#include <vtkAbstractCellLocator.h>
#include <vtkCellLocator.h>

// CellLocator
class VTKCELLLOCATORS_EXPORT CellLocator : public vtkCellLocator
{
public:
    static CellLocator *New();
    vtkTypeMacro(CellLocator, vtkCellLocator);
    // void PrintSelf(ostream &os, vtkIndent indent) override;

    /// @brief Search for the closest point on surface for all query points.
    /// @param points Query points
    /// @param cell_ids list to fill with the closest cell to each query points
    /// @param sub_ids list to fill with sub ids for the closest cell
    /// @return Points on surface that are closest to the query points.
    vtkSmartPointer<vtkPoints> FindClosestPoints(
        vtkPoints *points,
        vtkIdList *cell_ids = nullptr,
        vtkIdList *sub_ids = nullptr);

protected:
    CellLocator();
    ~CellLocator();

private:
    CellLocator(const CellLocator &) = delete;
    void operator=(const CellLocator &) = delete;
};

#endif
