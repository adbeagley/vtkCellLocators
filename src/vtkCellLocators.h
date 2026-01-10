// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef CellLocator_h
#define CellLocator_h

#include "vtkCellLocatorsModule.h" // for export macro>
#include <vtkPoints.h>
#include <vtkIdList.h>
#include <vtkAbstractCellLocator.h>
#include <vtkCellLocator.h>
#include <vtkStaticCellLocator.h>
#include <vtkOBBTree.h>

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
  StaticCellLocator();
  ~StaticCellLocator();

private:
  CellLocator(const CellLocator &) = delete;
  void operator=(const CellLocator &) = delete;
};

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
