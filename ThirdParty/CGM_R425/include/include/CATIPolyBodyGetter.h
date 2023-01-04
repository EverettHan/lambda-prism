// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyBodyGetter.h
//
//===================================================================
//
// June 2010  Creation: NDO
//===================================================================
#ifndef CATIPolyBodyGetter_H
#define CATIPolyBodyGetter_H

#include "PolyhedralModel.h"
#include "CATBaseUnknown.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByPolyhedralModel IID IID_CATIPolyBodyGetter;
#else
extern "C" const IID IID_CATIPolyBodyGetter ;
#endif

class CATPolyBody;


/**
Object modeler interface that provides access to a CATPolyBody.
*/
class ExportedByPolyhedralModel CATIPolyBodyGetter : public CATBaseUnknown
{
  CATDeclareInterface;

public:
     

  /**
   * Returns a CATPolyBody.
   * The returned instance should be released.
   * @param oPolyBody
   *   The returned CATPolyBody.
   * @return
   * <ul>
   *   <li> <code> S_OK </code> when a CATPolyBody is successfully returned.
   *   <li> <code> E_FAIL </code> or any other error if an error occurs.
   * </ul>
   */
  virtual HRESULT Get (CATPolyBody*& oPolyBody) = 0;

};

#endif
