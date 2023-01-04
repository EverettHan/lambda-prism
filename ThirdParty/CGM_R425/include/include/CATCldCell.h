//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldCell
//==============================================================================================================
// Creation: JLH - ??-Oct-1999
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldCell_H
#define CATCldCell_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldGenEntity.h"

//class CATCldBody ;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldCell ;
#else
extern "C" const IID IID_CATCldCell ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldCell</tt>.<br>
 * @see CATCldGenEntity
 */
class ExportedByCATGMGeometricInterfaces CATCldCell : public CATCldGenEntity
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// CATCldCell characteristics
//==============================================================================================================

  /**
   * Returns the fact that the cell is protected or not.
   */
  virtual CATBoolean IsProtected () const = 0 ;

  /**
   * Sets the cell as protected.
   */
  virtual void SetProtected () = 0 ;

  /**
   * Sets the cell as unprotected.
   */
  virtual void UnsetProtected () = 0 ;

  /**
   * Returns the fact that the cell is a uni-cell or not.
   */
  virtual CATBoolean IsAUniCell () const = 0 ;

  /**
   * Returns the fact that the cell is a multi-cell or not.
   */
  virtual CATBoolean IsAMultiCell () const = 0 ;

//==============================================================================================================
// Points.
//==============================================================================================================

  /**
   * Duplicates the given <tt>CATCldCell</tt> inside the current one.<br>
   * <b>CAUTION:</b> If the two <tt>CATCldCell</tt> share the same <tt>CATCldSetOfPoints</tt>,
   * there is duplication of the indexes and not of the points.
   */
  virtual void DuplicateInside (const CATCldCell* iOther) = 0 ;

//==============================================================================================================
// CNext methods
//==============================================================================================================

///**
// * Smart Use of Cloud :
// *   After its creation a cell is Modifiable.
// *   It becomes Non-Modifiable when a body containing it is Frozen .
// *
// *   For Smart manipulations of a body, one can first 'Touch' some cells of the body,
// *   then 'SmartDuplicate' the body in order to duplicate only the touched cells and
// *   the domains impacted by these modifications
// *
// *   A NonModifiable Touched Cell will be duplicated if you 'SmartDuplicate'
// *   a body containing it.
// */
//virtual CATBoolean IsTouched () = 0 ;
//virtual void       Touch (CATCldBody* iBodyForImpactPropagation) = 0 ;

} ;

CATDeclareHandler (CATCldCell, CATCldGenEntity) ;

#endif
