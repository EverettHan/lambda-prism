//=============================================================================
// Copyright Dassault Systemes Provence 2000-2003, all rights reserved
//=============================================================================
//
// CATFilletVariousParameters:
//
//=============================================================================
// Usage notes:
//=============================================================================
// 12/05/2005 : HLN : Herite de CATCGMVirtual
// 28/10/2004 : EAB : Versionning Interne
// 20/11/2003 : MWE ; ajout du point d'init
// 19/06/2003 : HLN : Creation
//=============================================================================
#ifndef CATFilletVariousParameters_h
#define CATFilletVariousParameters_h

#include "CATCGMVirtual.h"
#include "Connect.h"
#include "CATDataType.h"
class CATMathSetOfPointsND;

/**
 * The type of continuity constraint.
 * @param CATFrFPointCont
 * The point continuity (G0).
 * @param CATFrFTangentCont
 * The tangency continuity (G1).
 * @param CATFrFCurvatureCont
 * The curvature continuity (G2).
 */
typedef CATLONG32 CATSupportFilletContinuity;
/** @nodoc */
#define CATSupFilNoCont        -1
/** @nodoc */
#define CATSupFilPointCont      0
/** @nodoc */
#define CATSupFilTangentCont    1
/** @nodoc */
#define CATSupFilCurvatureCont  2

class CATSoftwareConfiguration;

class ExportedByConnect CATFilletVariousParameters : public CATCGMVirtual
{

public:

	//---------------------------------------------------------------
	// Constructor
	//---------------------------------------------------------------
  //Do not use - Use the constructor with CATSoftwareConfiguration
  CATFilletVariousParameters(CATSupportFilletContinuity iContinuityLevel1,
                             CATSupportFilletContinuity iContinuityLevel2,
                             CATMathSetOfPointsND * iInitPoint=0);

  CATFilletVariousParameters(CATSoftwareConfiguration * iConfig,
                             CATSupportFilletContinuity iContinuityLevel1,
                             CATSupportFilletContinuity iContinuityLevel2,
                             CATMathSetOfPointsND * iInitPoint=0);

	//---------------------------------------------------------------
	// Destructor
	//---------------------------------------------------------------

	~CATFilletVariousParameters();

	//---------------------------------------------------------------
	// Public Methods
	//---------------------------------------------------------------

  // Continuity level required between the fillet and each of both
  // support surfaces
  CATSupportFilletContinuity GetContinuityLevel1() const;
  CATSupportFilletContinuity GetContinuityLevel2() const;
  // Init point 
  // 5D point
  // U1, V1, U2, V2, Tspine
  //
  CATMathSetOfPointsND *GetInitPoint() const;

private:

	//---------------------------------------------------------------
	// Private Data : fields
	//---------------------------------------------------------------
	
  CATSupportFilletContinuity _ContinuityLevel1;
  CATSupportFilletContinuity _ContinuityLevel2;
  CATMathSetOfPointsND *_InitPoint;
  CATSoftwareConfiguration *_Config;
};

#endif
