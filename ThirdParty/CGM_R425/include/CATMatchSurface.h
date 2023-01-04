// COPYRIGHT DASSAULT SYSTEMES 1997 
//=============================================================================
//
// CATMatchSurface:
// Interface class of the Match Surface Operator.
//
//=============================================================================
//
// Usage notes:
// This class must be derived in order to implement specific algorithm or 
// capabilities (analytical or geometrical operators for example).
//
//=============================================================================
// July     97    Creation                       C.  Vergez-Samblancat
// Novembre 97    Modification                   J.  Bouix
// January  99    Modification	                 P-A Lourme
//=============================================================================

#ifndef CATMatchSurface_h
#define CATMatchSurface_h

#include "CATGMOperatorsInterfaces.h"
#include "CATFreeFormDef.h"
#include "CATTransitionCheckingCommand.h"
#include "CATCGMVirtual.h"

class CATCrvLimits;
class CATPLine;
class CATCurve;
class CATLaw;
class CATFrFCompositeCurve;
class CATFrFCCvLimits;
class CATMathDirection;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATMatchSurface : public CATCGMVirtual
{
  public :

    virtual ~CATMatchSurface();
    virtual void Run()=0;
    // Setting the Boundary to be matched. It defines the Surface to be matched : STBM
    virtual void SetCurveToBeMatched(const CATPLine *iFrontiere)=0;
   
    //=========================
    //  O L D   M E T H O D S 
    //=========================
    // Continuity constraint on the opposite boundary of the STBM.
    // The tranversal degre will be increased if necessary. The use of the
    // SetTransversalDegree method may be concurrent. If so, the degree given
    // by the SetTransversalDegree method is dominant.
    // iConstraint = 1 : Point Continuity
    // iConstraint = 2 : Tangent Continuity 
    // iConstraint = 3 : Curvature Continuity
    virtual void SetOppositeConstraint(CATLONG32 iConstraint) = 0;
    virtual CATLONG32 GetOppositeConstraint() const  = 0;
    // Setting the Reference side
    virtual void SetOppositeSideRefSurface() = 0;
    virtual void SetDefaultSideRefSurface() = 0;
    // Setting or changing the default orientation between the reference 
    // and the curve on the STBM (in order to manage manualy the twist).
    virtual void SetOppositeOrientation() = 0;
    virtual void SetDefaultOrientation() = 0; 

    //=========================
    //  N E W   M E T H O D S 
    //=========================

    // UseTheLastRunResult
    // The last run result defines the surface to be matched : the beginning
    // surface is changed. This allows a new match with the same operator, on the 
    // modified geometry.
    // The run method must have been called once before.
    virtual void UseTheLastRunResult() = 0;

    // Setting or reversing the default orientation between the reference 
    // and the curve on the STBM (in order to manage manualy the twist).
    virtual void SetDefaultReferenceOrientation() = 0; 
    virtual void ReverseReferenceOrientation() = 0;

    // Setting the Reference side
    virtual void SetDefaultReferenceSide() = 0;
    virtual void ReverseReferenceSide() = 0;

    // Connection Continuity
    // The default value is iContinuity = CATFrFPointCont
    virtual void SetConnectionContinuity(const CATFrFContinuity iContinuity) = 0;
    virtual CATFrFContinuity GetConnectionContinuity() const = 0; 
  
    // Continuity of the Opposite Side of the STBM
    // The tranversal degree will be increased if necessary. The use of the
    // SetTransversalDegree method may be concurrent. If so, the degree given
    // by the SetTransversalDegree method is dominant.
    // The default value is iContinuity = CATFrFPointCont
    virtual void SetOppositeSideContinuity(const CATFrFContinuity iContinuity) = 0;
    virtual CATFrFContinuity GetOppositeSideContinuity() const = 0; 

    // Tangent Parameter (with a connection continuity >= 1)
    // The operator applys a law on the STBM tangent norm. 
    // The default value is iLaw = constant law = 1.0.
    virtual void SetTangentParameter(const CATLaw * iLaw) = 0;
    virtual void GetTangentParameter(CATLaw *& oLaw) const = 0;

    // Tangent Direction (with a connection continuity >= 1)
    // The tangent direction of the STBM may take three values : 
    //    * The STBM tangent keeps its own direction (at a projection distortion),
    //      the tangent direction is FREE.
    //    * The tangent is collinear with the reference tangent,
    //      the tangent direction is COLLINEAR.
    //    * The angle is given by the user : a law is applied on the tangent
    //      direction in FREE mode.
    // iLaw is used only if iStartMode = iEndMode = FREE.
    // The default values are iStartMode = iEndMode = COLLINEAR.
    //                        iLaw = constant = 0.0
    virtual void SetTangentDirection(const CATFrFTangentDirection iStartMode,
				     const CATFrFTangentDirection iEndMode,
				     const CATLaw * iLaw = 0) = 0;
    virtual void GetTangentDirection(CATFrFTangentDirection & oStartMode,
				     CATFrFTangentDirection & oEndMode,
				     CATLaw * oLaw = 0) const = 0;

    // Diffusion  
    // iDiffusion = 0 : Matching creates only a local deformation.
    // iDiffusion = 1 : Deformation will be diffused along the STBM.
    virtual void SetDiffusion(const CATLONG32 iDiffusion) = 0;
    virtual CATLONG32 GetDiffusion() const = 0;

    // Homogenization
    // iHomogenization = 0 : the matching is at best,
    //      with the initial longitudinal degree of the surface to be matched, 
    //   or with a specified degree (using SetLongitudinalDegree(...))
    // iHomogenization = 1 : the matching is exact,the longitudinal degree of
    // the surface to be matched is adapted.
    virtual void SetHomogenization(const CATLONG32 iHomogenisation) = 0;
    virtual CATLONG32 GetHomogenization() const = 0;

    // Degrees
    // Longitudinal and transversal degrees constraints.
    // The SetLongitudinalDegree method should be called with Homogenization = 0.
    // The default values are the original degrees of the STBM. 
    virtual void SetLongitudinalDegree(CATLONG32 NLongi) = 0;
    virtual void SetTransversalDegree(CATLONG32 NTrans) = 0;
    virtual void GetDegrees(CATLONG32 &LongiD , CATLONG32 &TransD) const = 0;

    // ExtremitiesDirections
    // To have the extremities direction of the matched surface
    virtual void GetExtremitiesDirections(CATMathDirection * oStartTangent,
			                   CATMathDirection * oEndTangent,
					   double * oComputedAngles = 0) = 0;
    // PlanarOption
    // To set/unset the planar option. The planar option consists in moving
    // the control points in one direction. This direction may be constant, 
    // given by the user ; or it may be the local tangent plane normal.
    // iMode = 0  -->  unset the planar option,
    // iMode = 1  -->  set the option, with the local tangent plane normal,
    // iMode = 2  -->  set the option, with a given constant direction : iDirection.
    virtual void SetPlanarOption(CATLONG32 iMode, CATMathDirection * iDir = 0) = 0;

    // Check the transition quality
    // To get the maximum deviations. 
    // Use CATTransitionCheckingCommand.h for the command and the result.
    virtual void GetMaxDeviation(CATTransitionCheckingCommand iCmd,
				 CATTransitionDeviationResult &oDeviation) =0; 
};
#endif

