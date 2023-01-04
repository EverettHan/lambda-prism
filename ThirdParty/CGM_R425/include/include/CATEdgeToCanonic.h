/* -*-C++-*- */

#ifndef CATEdgeToCanonic_H
#define CATEdgeToCanonic_H 

// COPYRIGHT DASSAULT SYSTEMES 2021

//=============================================================================
//=============================================================================
//
// CATEdgeToCanonic :
// Class to retrieve a canonical CATCurve from a CATEdge
// This operator supports both exact and polyhedral CATEdge as input
// In case of polyhedral CATEdge, the returned canonical curve can be 
// the original one before converting exact into polyhedral,
// or a retrieved canonicity thanks to a recognition algorithm.
// In case of exact CATEdge, the behavior is equivalent to CATIPGMCurveToCanonic
// called with the EdgeCurve of the CATEdge between its 2 CATPointOnEdgeCurve as extremities.
//
//=============================================================================
// Usage notes:
//
// This operator can be used to retrieve the canonicity of an edge
//
//=============================================================================
// Feb 2021 Creation                                           DPS
//=============================================================================

#include "ExportedByCATTopologicalObjects.h" // ExportedBy
#include "CATCGMOperator.h"                  // derivation

#include "CATSkillValue.h"
#include "CATGeometryType.h"

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATSysBoolean.h"
#include "CATMathConstant.h" // CATAngle

class CATGeoFactory;
class CATEdgeToCanonicExt;
class CATSoftwareConfiguration;
class CATEdge;
class CATMathPoint;
class CATMathPlane;
class CATMathCircle;
class CATMathLine;
class CATCGMODTScaleManager;


class ExportedByCATTopologicalObjects CATEdgeToCanonic : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATEdgeToCanonic);

  public :  
  //-----------------------------------------------------------------------
  //- Object management 
  //-----------------------------------------------------------------------

  // Constructor : do not use, Use CATCreateEdgeToCanonic instead
  CATEdgeToCanonic(CATGeoFactory & iFactory, CATEdgeToCanonicExt & iGeoExtension);

  // Destructor
  ~CATEdgeToCanonic();


  //-----------------------------------------------------------------------
  //- Public Settings
  //-----------------------------------------------------------------------

  // Setting methods

  // Specify type of canonical geometry requested
  // possible types are : CATLineType, CATCircleType, CATConicType, CATEllipseType ...
  void SetRequestedType(const CATGeometricType iRequestedType);

  void SetTolerance(double iTolerance);

  // Multi-Run mode : can Reset the input edge before Run()
  void SetEdge(CATEdge * iEdge);

    
  //-----------------------------------------------------------------------
  //- Public Get Methods
  //-----------------------------------------------------------------------

  // Returns canonical equivalent curve
  // returns 0 if no canonical equivalent curve has been found
  // The caller becomes responsible of the Life Cycle Managment of the returned CATCurve :
  // please call CATGeoFactory->Remove() in order to release the CATCurve after use.
  CATCurve * GetResult();

  // Returns canonical equivalent curve with the Curve limits matching with the input CATEdge
  // returns 0 if no canonical equivalent curve has been found
  // The caller becomes responsible of the Life Cycle Management of the returned CATCurve :
  // please call CATGeoFactory->Remove() in order to release the CATCurve after use.
  CATCurve * GetResult(CATCrvLimits & oLimits);


  // Retrieve specific canonicity after Run
  // It's not necessary to get the CATCurve before calling these methods
  // returns FALSE if these methods are called before Run, or if the operator has been created with invalid data
  CATBoolean IsLinear();
  CATBoolean IsLinear(CATMathLine & oLine);
  CATBoolean IsLinear(CATMathPoint & oStartLinePoint, CATMathPoint & oEndLinePoint);

  CATBoolean IsCircular();
  CATBoolean IsCircular(CATMathCircle & oCircle);
  CATBoolean IsCircular(CATMathPlane & oCircleSupport, double & oRadius, CATAngle & oStartAngle, CATAngle & oEndAngle);


protected:

  //------------------------------------------------------
  // Run
  //------------------------------------------------------
  virtual int                                RunOperator();


  // ------------------
  // CGMReplay Methods
  // ------------------

public :
  /** @nodoc * @nocgmitf */
  virtual /* CATCGMOperator method */ const CATString * GetOperatorId();

  /** @nodoc * @nocgmitf
  * For CGMReplay only */
  void SetCGMODTScaleManager(CATCGMODTScaleManager * iScaleManager);


private :

  CATEdgeToCanonicExt &      _EdgeToCanonicExtension;
};

/**
 * Creates the CATEdgeToCanonic operator from an edge
 * @param iFactory
 * The factory where new geometric objects will be created.
 * @param iSoftwareConfiguration
 * The pointer to the software configuration
 * @param iEdgeToCanonic
 * The edge to retrieve the canonicity knowledge
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation without any option.
 *     <dt><tt>ADVANCED</tt>  :
 * mode, options can be precised with the <tt>SetXxx</tt> methods,
 * <dd>Use the <tt>Run</tt> method to computes the operation.</dl>
 * @return [out, IUnknown#Release]
 *The pointer to the created operator.
 */
ExportedByCATTopologicalObjects CATEdgeToCanonic * CATCreateEdgeToCanonic(CATGeoFactory            * iFactory,
                                                                          CATSoftwareConfiguration * iConfig,
                                                                          CATEdge                  * iEdgeToCanonic,
                                                                          CATSkillValue              iMode = ADVANCED);

#endif







