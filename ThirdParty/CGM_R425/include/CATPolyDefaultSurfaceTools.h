// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyDefaultSurfaceTools.h
//
//===================================================================
// November 2014  Creation: NDO
//===================================================================
#ifndef CATPolyDefaultSurfaceTools_H
#define CATPolyDefaultSurfaceTools_H

#include "PolyMeshTools.h"
#include "CATIPolySurfaceTools.h"


/**
Default implementation of the CATIPolySurfaceTools.
An instance of this class can only be constructed by a derived class (constructor is protected.)
*/
class ExportedByPolyMeshTools CATPolyDefaultSurfaceTools : public CATIPolySurfaceTools
{

public:

  virtual HRESULT AddVertexNormalLayer (CATIPolySurface& iPolySurface) const;

protected:

  /**
   * Proctected constructor.
   * An instance of this class can only be constructed by a derived class.
   */
  CATPolyDefaultSurfaceTools () {}

};

#endif
