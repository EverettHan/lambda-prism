// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceVertexCellLayer.h
//
//===================================================================
// February 2009  Creation: NDO
//===================================================================
#ifndef CATPolySurfaceVertexCellLayer_H
#define CATPolySurfaceVertexCellLayer_H

#include "PolyMeshImpl.h"
#include "CATIPolySurfaceVertexCellLayer.h"
#include "CATPolySurfaceVertexCellConstLayer.h"
#include "CATMapOfIntToInt.h"

class CATPolyFace;
class CATPolyBodyDiagnosis;
class CATPolyBodyCheckerObserver;


/**
This is an editable surface vertex cell layer.
*/
class ExportedByPolyMeshImpl CATPolySurfaceVertexCellLayer : public CATIPolySurfaceVertexCellLayer
{

public:

  /**
   * Constructs a new CATPolySurfaceVertexCellConstLayer for a face.
   * @param iPolyFace
   *   The input CATPolyFace.
   * @param iDiagnosis
   *   An optional object to log the errors encountered during the construction of the surface vertex cell layer.
   * @param obs
   *   An optional object to finer log errors.
   */
  static CATPolySurfaceVertexCellLayer* New (const CATPolyFace& iPolyFace, CATPolyBodyDiagnosis* ioDiagnosis = 0, CATPolyBodyCheckerObserver* obs = 0);

public:

  HRESULT Set (int iVertex, CATPolyCell* iCell, int iCellVertex);

  HRESULT Get (int iVertex, CATPolyCell*& oCell, int& oCellVertex) const;

public:

  /**
   * Returns the size of the object in bytes.
   */
  unsigned int SizeOf () const;

private:

  typedef CATPolySurfaceVertexCellConstLayer::Cell Cell;

  unsigned int _NbAllocatedCells;
  unsigned int _IncrementalSize;

  Cell* _Cells;                       // Array of cells.
  CATMapOfIntToInt _MapVertexToCell;  // Map a micro-vertex to its cell in the above array.

private:

  /**
   * Reallocates the cell array.
   */ 
  HRESULT Reallocate (unsigned int nbCellsToAllocate);

  /**
   * Constructs a surface vertex layer for a given number of cells.
   */
  CATPolySurfaceVertexCellLayer (unsigned int iNbVertexCells);

  virtual ~CATPolySurfaceVertexCellLayer ();

};

#endif
