// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : VB7
//
// DESCRIPTION  : Given two bodies and a mirror plane, this operator provides the pairs of symmetric faces.
//
// INPUT DATA   : 
//                - First body
//                - Second body
//                - Mirror Plane
//
// OPTIONS      : 
//                - Tolerance
//
// OUTPUT DATA  :
//                - List of symmetrical faces on the first body  -- parallel to the following list
//                - List of symmetrical faces on the second body -- parallel to the previous list
//                - List of non-symmetrical faces on the first body
//                - List of non-symmetrical faces on the second body
//
//=============================================================================
// Creation VB7 December 2018
//=============================================================================

#ifndef CATIPGMBodySymmetryOpe_h_
#define CATIPGMBodySymmetryOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2019

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPersistentOperator.h"
#include "ListPOfCATFace.h"

class CATGMBodySymmetryImpl;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMBodySymmetryOpe;

class ExportedByCATGMOperatorsInterfaces CATIPGMBodySymmetryOpe: public CATIPGMPersistentOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMBodySymmetryOpe();

  //------------------
  // Set methods
  //------------------
  virtual void SetTolerance(double iTolerance) = 0;

  //------------------
  // Get methods
  //------------------
  virtual void GetSymmetricFaceLists(
    CATLISTP(CATFace) &oFirstBodySymmetricFaceList,
    CATLISTP(CATFace) &oSecondBodySymmetricFaceList) = 0;

  virtual void GetNonSymmetricFaceLists(
    CATLISTP(CATFace) &oFirstBodyNonSymmetricFaceList,
    CATLISTP(CATFace) &oSecondBodyNonSymmetricFaceList) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMBodySymmetryOpe(); // -> delete can't be called
};

// ----------------------
// CATPGMCreateGMBodySymmetryOpe
// ----------------------
ExportedByCATGMOperatorsInterfaces CATIPGMBodySymmetryOpe *CATPGMCreateGMBodySymmetryOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iFirstBody,
  CATBody &iSecondBody,
  CATMathPlane &iMirrorPlane);

#endif /* CATIPGMBodySymmetryOpe_h_ */
