// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyPointTools.h
//
//===================================================================
//
// February 2010  Creation: NDO
//===================================================================
#ifndef CATIPolyPointTools_H
#define CATIPolyPointTools_H

#include "PolyhedralModel.h"
#include "CATErrorDef.h" 

class CATIPolyPoint;
class CATPolyVertex;


/**
 * The use of polyhedral tools (this class) is reserved exclusively to polyhedral frameworks.
 * Do not use anywhere else.
 * Use instead the global functions and services that are defined in CATPolyServices.h.
 * 
 * @see CATPolyServices.h
 */
class ExportedByPolyhedralModel CATIPolyPointTools
{

public:

  virtual ~CATIPolyPointTools () {}

public:

  /**
   * Attaches a CATPolyVertex to the CATIPolyPoint.
   * A CATIPolyPoint can refer to one and only one CATPolyVertex.
   * @param iPolyPoint
   *   The input CATIPolyPoint.
   * @param iPolyVertex
   *   The input CATPolyVertex to attach.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The vertex is successfully attached.
   *     <li> <tt>S_FALSE</tt> The vertex cannot be attached.
   *     <li> <tt>E_FAIL</tt> An error occured.
   *   </ul>
   */
  virtual HRESULT AttachVertex (CATIPolyPoint& iPolyPoint, const CATPolyVertex* iPolyVertex) const = 0;

  /**
   * Detaches a CATPolyVertex from the CATIPolyPoint.
   * @param iPolyPoint
   *   The input CATIPolyPoint.
   * @param iPolyVertex
   *   The input CATPolyVertex to detach.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> The vertex is successfully detached.
   *     <li> <tt>S_FALSE</tt> The vertex cannot be detached.
   *     <li> <tt>E_FAIL</tt> An error occured.
   *   </ul>
   */
  virtual HRESULT DetachVertex (CATIPolyPoint& iPolyPoint, const CATPolyVertex* iPolyVertex) const = 0;

protected:

  CATIPolyPointTools () {}

};

#endif // !CATIPolyPointTools_H
