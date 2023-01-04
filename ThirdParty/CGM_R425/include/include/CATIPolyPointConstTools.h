// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
//  CATIPolyPointConstTools.h
//
//===================================================================
//
// February 2010  Creation: NDO
//===================================================================
#ifndef  CATIPolyPointConstTools_H
#define  CATIPolyPointConstTools_H

#include "PolyhedralModel.h"
#include "CATErrorDef.h" 
#include "CATBoolean.h"

class CATIPolyPoint;


/**
 * The use of polyhedral tools (this class) is reserved exclusively to polyhedral frameworks.
 * Do not use anywhere else.
 * Use instead the global functions and services that are defined in CATPolyServices.h.
 * 
 * @see CATPolyServices.h
 */
class ExportedByPolyhedralModel CATIPolyPointConstTools
{

public:

  virtual ~CATIPolyPointConstTools () {}

public:

  //
  // MISCELLANEOUS
  //

  /**
   * Returns the ID or CGM ID associated to the point if available.
   */
  virtual HRESULT GetID (const CATIPolyPoint& iPolyPoint, unsigned int& oID) const = 0;

  /**
   * Returns the size in bytes of the CATIPolyPoint and its layers.
   * The size of the dependent objects is not included.
   */
  virtual unsigned int SizeOf (const CATIPolyPoint& iPolyPoint) const = 0;

  /**
   * Returns <tt>TRUE</tt> if the CATIPolyPoint shares its data with another CATIPolyPoint.
   */
  virtual CATBoolean ShareDataWith (const CATIPolyPoint& iPolyPoint, const CATIPolyPoint& iWithPolyPoint) const = 0;

protected:

   CATIPolyPointConstTools () {}

};

#endif // ! CATIPolyPointConstTools_H
