#ifndef StaticCellLocator_h
#define StaticCellLocator_h

#include "vtkCellLocatorsModule.h" // for export macro>
#include <vtkPoints.h>
#include <vtkIdList.h>
#include <vtkStaticCellLocator.h>

class VTKCELLLOCATORS_EXPORT StaticCellLocator : public vtkStaticCellLocator
{
public:
  static StaticCellLocator *New();
  vtkTypeMacro(StaticCellLocator, vtkStaticCellLocator);
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
  StaticCellLocator();
  ~StaticCellLocator();

private:
  StaticCellLocator(const StaticCellLocator &) = delete;
  void operator=(const StaticCellLocator &) = delete;
};

#endif
