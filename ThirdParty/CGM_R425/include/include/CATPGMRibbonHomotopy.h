#ifndef CATPGMRibbonHomotopy_h_
#define CATPGMRibbonHomotopy_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATCollec.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATConnectStartHomotopy;
class CATIPGMConnectTool;
class CATCurve;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATTopData;
class CATMathPoint;

//--------------------------------------------------------------------------
// class CATRibbonHomotopy
// -------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATPGMRibbonHomotopy
{
public:
  /**
   * Constructor
   */
  CATPGMRibbonHomotopy();

  /**
   * Destructor
   */
  virtual ~CATPGMRibbonHomotopy();

  //--------------------------------------------------------------------------
  // Method GetCurve
  // returns a circle (fillet) or a line (chamfer)
  //--------------------------------------------------------------------------
  virtual CATCurve *GetCurve() = 0;

  //--------------------------------------------------------------------------
  // Method SetHoldCurve
  // Method to set a hold curve for hold curve chamfer type. Hold edge and 
  // chamfer edge need to share the ref face given in constructor. Method
  // needs to be called before the Run Method
  //--------------------------------------------------------------------------
  virtual void SetHoldCurve(CATEdge *iHoldEdge) = 0;

  //--------------------------------------------------------------------------
  // Method Run
  //--------------------------------------------------------------------------
  virtual void Run() = 0;

  //--------------------------------------------------------------------------
  // Method GetDiagnostic
  // Returns 
  // 0 if there is no solution
  // 1 if there is an exact solution
  // 2 if the solution is obtained with the tangent planes
  //--------------------------------------------------------------------------
  virtual CATLONG32 GetDiagnostic() = 0;
};

//-------------------------------------------------------------------------- 
// Constructor
// With an Edge of a Body and a point on this edge,
// returns the previsu of a fillet or a chamfer. 
//
// iRefFace est une face de reference pour la previsu du chamfrein.
//--------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATPGMRibbonHomotopy *CATPGMCreateRibbonHomotopy(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATEdge *iEdge,
  const CATMathPoint &iPoint,
  CATIPGMConnectTool *iProfilePtr,
  CATFace *iRefFace = NULL);

//-------------------------------------------------------------------------- 
// Old constructor : Do not use
//--------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATPGMRibbonHomotopy *CATPGMCreateRibbonHomotopy(
  CATBody *iBody,
  CATEdge *iEdge,
  const CATMathPoint &iPoint,
  CATGeoFactory *iFactory,
  CATIPGMConnectTool *iProfilePtr,
  CATFace *iRefFace = NULL);

#endif /* CATPGMRibbonHomotopy_h_ */
