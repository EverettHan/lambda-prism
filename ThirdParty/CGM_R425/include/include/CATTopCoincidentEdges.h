// COPYRIGHT DASSAULT SYSTEMES 2017
//=============================================================================
//
// CATTopCoincidentEdges: 
//  Specific data for Composite: Pair of coincident edges. 
//
//
//=============================================================================
//
// Usage notes:
//
//
//
//=============================================================================
//  June 2017  Creation                                                   U29
//=============================================================================

#ifndef CATTopCoincidentEdges_H
#define CATTopCoincidentEdges_H

class CATBody;
class CATListPtrCATBody;

#include "CATCEF_OperatorDef.h"
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATTopCoincidentEdges
{

public:

  /**
  * Destructor
  */
  virtual ~CATTopCoincidentEdges();

  /**
  * Retrieve the body representing the coincidence area.
  *  @return
  *    The "coincidence" body.
  */
  virtual CATBody * GetCoincidenceBody() const = 0;

  /**
  *  @return
  *    the coincidence type between the edges, ie: OVERLAP or BUTT.
  *  @see CATCEF_OperatorDef.h for more information.
  */
  virtual CATCoincidenceType GetCoincidenceType() const = 0;

  /**
  * Retrieve the corresponding input contours that generate this result.
  *  @param oAncestorBodies
  *    Corresponding input plies.
  */
  virtual void GetAncestorBodies(CATListPtrCATBody& ioAncestorBodies) const = 0;
};

#endif
