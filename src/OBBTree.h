#ifndef OBBTree_h
#define OBBTree_h

#include "vtkCellLocatorsModule.h" // for export macro>
#include <vtkPoints.h>
#include <vtkIdList.h>
#include <vtkObject.h>
#include <vtkLocator.h>
#include <vtkAbstractCellLocator.h>
#include <vtkOBBTree.h>
#include <vtkABI.h>
#include "vtkABINamespace.h"

class VTKCELLLOCATORS_EXPORT OBBTree : public vtkOBBTree
{
public:
    static OBBTree *New();
    vtkTypeMacro(OBBTree, vtkOBBTree);
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
    OBBTree();
    ~OBBTree();

private:
    OBBTree(const OBBTree &) = delete;
    void operator=(const OBBTree &) = delete;
};

#endif
