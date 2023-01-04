#ifndef CATPGMIntersectFilteringTools_h_
#define CATPGMIntersectFilteringTools_h_

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATCollec.h"
#include "ListPOfCATFace.h"

class CATBody;
class CATFace;

/**
 * @level Protected
 * @usage U1
 */
/**
* Class defining the filtering interfaces for boolean operations.
* Use with caution since this implies an incomplete operation and,
* most of the time, an invalid result body (self-intersecting).
* Several of following interfaces are incompatible between them:
* You cannot specify Faces Only and Not to intersect on a same input body.
* An internal error is thrown in these configurations.
*/
class ExportedByCATGMModelInterfaces CATPGMIntersectFilteringTools: public CATBaseUnknown
{
public:
  /**
   * Constructor
   */
  CATPGMIntersectFilteringTools();

  /** 
   * Faces of the given Body which will be the only ones intersected 
   * with the other input body (completely or partially if it has 
   * also a given List of Faces)
   */
  virtual void SetFacesOnlyToIntersect(
    CATBody *ipBody,
    const CATLISTP(CATFace) &iListOfFaces) = 0;

  /** 
   * Faces of the given Body which will not be intersected 
   * with the other input body
   */
  virtual void SetFacesNotToIntersect(
    CATBody *ipBody,
    const CATLISTP(CATFace) &iListOfFaces) = 0;

  /** 
   * The question
   */
  virtual CATBoolean IsToIntersect(CATFace *ipFaceOfBody1, CATFace *ipFaceOfBody2) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATPGMIntersectFilteringTools();
};

/** 
 * Creates a CATPGMIntersectFilteringTools
 * ipBodies are the input bodies of the associated Boolean operator
 * @return [out, CATBaseUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATPGMIntersectFilteringTools *CATPGMCreateIntersectFilteringTools(
  CATBody *ipBody1,
  CATBody *ipBody2);

#endif /* CATPGMIntersectFilteringTools_h_ */
