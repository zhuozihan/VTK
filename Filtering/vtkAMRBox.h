/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkAMRBox.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkAMRBox - Encloses a rectangular region of voxel like cells.
//
// .SECTION Description
// vtkAMRBox represents a collection of voxel like cells that fill
// a rectangular region. It's purpose is to facilitate manipulation
// of cell data arrays and the blocks that they are defined on.
//
// The vtkAMRBox can be either 2D or 3D. For 2D grids, pointers
// passed in are assumed to be 2 units. The default is 3D.
//
// vtkAMRBox is used in vtkHierarchicalBoxDataSet to compute cell visibilty.
//
// .SECTION See Also
// vtkHierarachicalBoxDataSet, vtkAMRBoxUtilities.hxx

#ifndef __vtkAMRBox_h
#define __vtkAMRBox_h

#include "vtkObject.h"

class VTK_FILTERING_EXPORT vtkAMRBox
{
public:
  // Description:
  // Construct the empty box.
  vtkAMRBox(int dim=3);
  // Description:
  // Construct a specific 3D box.
  vtkAMRBox(
      vtkIdType ilo,vtkIdType jlo,vtkIdType klo,
      vtkIdType ihi,vtkIdType jhi,vtkIdType khi);
  // Description:
  // Construct a specific 2D box.
  vtkAMRBox(
      vtkIdType ilo,vtkIdType jlo,
      vtkIdType ihi,vtkIdType jhi);
  // Description:
  // Construct a specific box. (ilo,jlo,klo,)(ihi,jhi,khi)
  vtkAMRBox(int dim, const vtkIdType lo[3], const vtkIdType hi[3]);
  vtkAMRBox(const vtkIdType lo[3], const vtkIdType hi[3]);
  // Description:
  // Construct a specific box. (ilo,ihi, jlo,jhi, klo,khi)
  vtkAMRBox(int dim, const vtkIdType dims[6]);
  vtkAMRBox(const vtkIdType dims[6]);
  // Description:
  // Copy construct this box from another.
  vtkAMRBox(const vtkAMRBox &other);
  // Description:
  // Copy the other box to this box.
  vtkAMRBox &operator=(const vtkAMRBox &other);
  // Description:
  // Set the box to null;
  void Invalidate();
  // Description:
  // Get/Set the spatial dimension of the box. Only 2 and 3 
  // are valid.
  int GetDimensionality() const { return this->Dimension; }
  void SetDimensionality(int dim);
  // Description:
  // Set the dimensions of the box. ilo,jlo,klo,ihi,jhi,khi
  void SetDimensions(
      vtkIdType ilo, vtkIdType jlo, vtkIdType klo,
      vtkIdType ihi, vtkIdType jhi, vtkIdType khi);
  // Description:
  // Set the dimensions of the box. (ilo,jlo,klo),(ihi,jhi,khi)
  void SetDimensions(const vtkIdType lo[3], const vtkIdType hi[3]);
  // Description:
  // Set the dimensions of the box. (ilo,ihi,jlo,jhi,klo,khi)
  void SetDimensions(const vtkIdType dims[6]);
  // Description:
  // Get the dimensions of this box. (ilo,jlo,jhi),(ihi,jhi,khi)
  void GetDimensions(vtkIdType lo[3], vtkIdType hi[3]) const;
  // Description:
  // Get the dimensions of this box. (ilo,ihi, jlo,jhi, klo,khi)
  void GetDimensions(vtkIdType dims[6]) const;
  // Description:
  // Get the low corner index.
  void GetLoCorner(vtkIdType lo[3]) const;
  const vtkIdType *GetLoCorner() const { return this->LoCorner; }
  // Description:
  // Copy the high corner index.
  void GetHiCorner(vtkIdType hi[3]) const;
  const vtkIdType *GetHiCorner() const { return this->HiCorner; }
  // Description:
  // Gets the number of cells enclosed by the box.
  void GetNumberOfCells(vtkIdType ext[3]) const;
  vtkIdType GetNumberOfCells() const;
  // Description:
  // Gets the number of nodes required to construct
  // a physical representation of the box.
  void GetNumberOfNodes(vtkIdType ext[3]) const;
  vtkIdType GetNumberOfNodes() const;
  // Description:
  // Set/Get grid spacing. Refine/coarsen operations update
  // the grid spacing.
  const double *GetGridSpacing() const { return this->DX; }
  void GetGridSpacing(double dX[3]) const;
  void SetGridSpacing(double dx);
  void SetGridSpacing(const double dX[3]);
  void SetGridSpacing(double dx, double dy, double dz);
  // Description:
  // Set/Get world space origin of the data set, The origin
  // is the location of the low corner cell's low corner node
  // of the data set. Which is not necessarilly the origin of
  // this box! For that use GetBoxOrigin().
  const double *GetDataSetOrigin() const { return this->X0; }
  void GetDataSetOrigin(double X0[3]) const;
  void SetDataSetOrigin(const double X0[3]);
  void SetDataSetOrigin(double x0, double y0, double z0);
  // Description:
  // Get the world space origin of this box. The origin is the
  // location of the lower corner cell's lower corner node,
  // which is not necessarilly the orgin of the data set! For
  // that use GetDataSetOrigin(). The value is computed each time,
  // so that operations on the box are are appropriately reflected.
  void GetBoxOrigin(double x0[3]) const;
  // Description:
  // Grows the box in all directions.
  void Grow(vtkIdType byN);
  // Description:
  // Shrinks the box in all directions.
  void Shrink(vtkIdType byN);
  // Description:
  // Shifts the box in index space.
  void Shift(vtkIdType i, vtkIdType j);
  void Shift(vtkIdType i, vtkIdType j, vtkIdType k);
  void Shift(const vtkIdType I[3]);
  // Description:
  // Test if this box is empty/valid.
  bool Empty() const;
  // Description:
  // Test if this box has the same dimensions as another.
  bool operator==(const vtkAMRBox &other);
  // Description:
  // Intersect this box with another box in place.
  void operator&=(const vtkAMRBox &rhs);
  // Description:
  // Test to see if a given cell index is inside this box.
  bool Contains(vtkIdType i,vtkIdType j,vtkIdType k) const;
  bool Contains(const vtkIdType I[3]) const;
  // Description:
  // Test to see if a given box is inside this box.
  bool Contains(const vtkAMRBox &other) const;
  // Description:
  // Refine the box.
  void Refine(int r);
  // Description:
  // Coarsen the box.
  void Coarsen(int r);
  // Description:
  // Send the box to a stream. "(ilo,jlo,jhi),(ihi,jhi,khi)"
  ostream &Print(ostream &os) const;

  //BTX
  // @deprecated Replaced by Contains() as of VTK 5.4.
  // Do not use! See Contains().
  VTK_LEGACY(int DoesContainCell(int i, int j, int k));
  // @deprecated Replaced by Contains() as of VTK 5.4.
  // Do not use! See Contains().
  VTK_LEGACY(int DoesContainBox(vtkAMRBox const & box) const);
  //ETX

public:
  // Description:
  // These are public for backward compatibility only. If your
  // code uses these, it will break in the future when this class
  // is fixed. Use the above Set/Get'ers. See Get/SetDimensions, 
  // Get/SetXCorner, and the many constructors above.
  vtkIdType LoCorner[3]; // lo corner cell id.
  vtkIdType HiCorner[3]; // hi corner cell id.
private:
  int Dimension;         // 2 or 3.
  double X0[3];          // Dataset origin (not box origin). low corner cell's, low corner node.
  double DX[3];          // grid spacing.
};




// NOTE 2008-11-10
// If you are using this to set public member variables, DONT.
// It is here for now for the sake of backward compatibility.
// Use the Set'ers.

// Helper to unroll the loop
template<int dimension>
struct vtkAMRBoxInitializeHelp;

template<int dimension>
void vtkAMRBoxInitialize(int *LoCorner, int *HiCorner, // member
                         const int *loCorner, const int *hiCorner, // local
                         vtkAMRBoxInitializeHelp<dimension>* = 0) // dummy parameter for vs6
  {
  for(int i=0; i<dimension; ++i)
    {
    LoCorner[i] = loCorner[i];
    HiCorner[i] = hiCorner[i];
    }
  for(int i=dimension; i<(3-dimension); ++i)
    {
    LoCorner[i] = 0;
    HiCorner[i] = 0;
    }
  }



#endif
