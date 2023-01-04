#ifndef CATIntersectFilteringTools_H_
#define CATIntersectFilteringTools_H_

// COPYRIGHT DASSAULT SYSTEMES  2012

#include "BOOLEAN.h"
#include "CATPGMIntersectFilteringTools.h"
#include "CATCollec.h"
#include "ListPOfCATFace.h"

#include "CATSubdIntersectingFunction.h"

class CATBody;
class CATFace;

class CATCGMStream;
class CATCGMOutput;
class CATCXSmartBodyDuplicator;
class CATCGMHashTable;

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
class ExportedByBOOLEAN CATIntersectFilteringTools: public CATPGMIntersectFilteringTools
{
public:
  /** 
   * @nodoc @nocgmitf
   * Constructor: ipBodies are the input bodies of the Boolean operator 
   */
  CATIntersectFilteringTools(CATBody * ipBody1, CATBody * ipBody2);
  /** @nodoc @nocgmitf */
  CATIntersectFilteringTools();

  /** @nodoc @nocgmitf */
  void SetBodies(CATBody * ipBody1, CATBody * ipBody2);

  /** 
   * @nodoc @nocgmitf
   * Function test before each Face-Face intersection
   */
  void SetIntersectingFunction(IntersectingFunction      iFunction    );
  /** 
   * @nodoc @nocgmitf
   * Deprecated, use the following ones
   */
  void SetContactFacesForUnion(CATBody                 * ipBody       , 
                               const CATLISTP(CATFace) & iContactFaces);
  /** 
   * Faces of the given Body which will be the only ones intersected 
   * with the other input body (completely or partially if it has 
   * also a given List of Faces)
   */
  void SetFacesOnlyToIntersect(CATBody                 * ipBody       , 
                               const CATLISTP(CATFace) & iListOfFaces );
  /** 
   * Faces of the given Body which will not be intersected 
   * with the other input body
   */
  void SetFacesNotToIntersect (CATBody                 * ipBody       , 
                               const CATLISTP(CATFace) & iListOfFaces );

  /** 
   * @nodoc @nocgmitf
   * To forward the Only and Not To Intersect accross the Duplication
   */
  void IntegrateDuplication(CATCXSmartBodyDuplicator * ipDuplicator);

  /** 
   * The question
   */
  virtual CATBoolean IsToIntersect(CATFace * ipFaceOfBody1, CATFace * ipFaceOfBody2);
  
  /** @nodoc @nocgmitf */
  CATBoolean IsThereFiltering();

  /** 
   * @nodoc @nocgmitf
   * CGMReplay methods
   */
  void Write(CATCGMStream & Str);
  /** @nodoc @nocgmitf */
  void Read(CATCGMStream & Str);
  /** @nodoc @nocgmitf */
  void SetInto(CATIntersectFilteringTools * & iopOp);
  /** @nodoc @nocgmitf */
  void Dump(CATCGMOutput & os);

  /** 
   * @nodoc @nocgmitf
   * Internal data
   */
  CATBody            * _pBody1;
  /** @nodoc @nocgmitf */
  CATBody            * _pBody2;
  /** 
   * @nodoc @nocgmitf
   * Old filtering method's data
   */
  int                  _AttributeKey;
  /** @nodoc @nocgmitf */
  short                _OptimizedOnBody[2];
  /** @nodoc @nocgmitf */
  IntersectingFunction _IntersectingFunction;
  /** 
   * @nodoc @nocgmitf
   * New filtering method's lists of faces
   */
  CATCGMHashTable    * _pHTableOfOnlyOfBody1;
  /** @nodoc @nocgmitf */
  CATCGMHashTable    * _pHTableOfOnlyOfBody2;
  /** @nodoc @nocgmitf */
  CATCGMHashTable    * _pHTableOfNotOfBody1;
  /** @nodoc @nocgmitf */
  CATCGMHashTable    * _pHTableOfNotOfBody2;

protected:
  /** @nodoc @nocgmitf */
  virtual ~CATIntersectFilteringTools();
};

/** 
 * Creates a CATIntersectFilteringTools
 * ipBodies are the input bodies of the associated Boolean operator
 * @return [out, CATBaseUnknown#Release]
 */
ExportedByBOOLEAN CATIntersectFilteringTools * CATCreateIntersectFilteringTools(CATBody * ipBody1, CATBody * ipBody2);

#endif

