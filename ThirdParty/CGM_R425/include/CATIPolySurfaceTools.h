// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceTools.h
//
//===================================================================
// October 2009  Creation: NDO
// January 2012  Modification JXO: AddVertexNormalLayer
//===================================================================
#ifndef CATIPolySurfaceTools_H
#define CATIPolySurfaceTools_H

#include "PolyhedralModel.h"
#include "CATErrorDef.h" 

class CATIPolySurface;


/**
 * The use of polyhedral tools (this class) is reserved exclusively to polyhedral frameworks.
 * Do not use anywhere else.
 * Use instead the global functions and services that are defined in CATPolyServices.h.
 * 
 * @see CATPolyServices.h
 */
class ExportedByPolyhedralModel CATIPolySurfaceTools
{

public:

  virtual ~CATIPolySurfaceTools () {}

public:

  /**
   * Adds a Normal layer to an editable mesh.
   * @param iPolySurface
   *   The input CATIPolySurface.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The layer successfully added.
   *     <li> <tt>S_FALSE</tt> The layer already existed.
   *     <li> <tt>E_FAIL</tt> The input poly surface is not editable.
   *     <li> <tt>E_OUTOFMEMORY</tt> The world is on the verge of apocalypse.
   *   </ul>
   */
  virtual HRESULT AddVertexNormalLayer (CATIPolySurface& iPolySurface) const = 0;

protected:

  CATIPolySurfaceTools () {}

};

#endif // !CATIPolySurfaceTools_H
