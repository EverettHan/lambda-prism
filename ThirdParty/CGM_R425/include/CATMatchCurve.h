// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATMatchCurve:
// Interface class of the Match Curve Operator.
//
//=============================================================================
//
// Usage notes:
// This class can be used as is for simple Match Curve or derived
// in order to implement specific algorithm or capabilities.
//
//=============================================================================
// January 1998     Creation                   J. Bouix
//=============================================================================

#ifndef CATMatchCurve_H
#define CATMatchCurve_H

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATPGMCreateMatchCurve.h"
#include "CATCGMVirtual.h"

class CATPLine;
class CATCurve;
class CATCrvParam;
class CATPointOnCurve;
class CATPoint;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATMatchCurve  : public CATCGMVirtual
{
  public :
    
    virtual  ~CATMatchCurve();
    virtual void Run()=0;

    // Setting LimitPoint of the Curve To Be Matched (CTBM)
    virtual void SetLimitPoint(const CATPointOnCurve * iLimitPoint) = 0;
  
    
    // Setting the reference point on the reference curve
    virtual void SetReferencePoint(CATPoint * iRefPoint ) = 0;
    // DO NOT USE
    virtual void SetReferenceCurveParam(const CATCrvParam & iRefPtParam ) = 0; 


  //-------------------------------------
  // Methods which define configuration :
  //-------------------------------------

    //  Type of transition continuity
    // 1  : C0 (Default)
    // 2  : Colinear tangents (C1)
    // 3  : Curvature continuity (C2)
    virtual   void SetTransitionContinuity(const CATLONG32 Continuity) = 0;
    virtual   CATLONG32 GetTransitionContinuity() const = 0; 
  
    // Constraint on the opposite side of the boundary to be matched,
    // tranversal degre will be increased if necessary.
    // C0 -> 1 (Default) ; C1 -> 2 ; C2 -> 3   
    virtual void SetOppositeConstraint(const CATLONG32 iConstraint) = 0;
    virtual CATLONG32 GetOppositeConstraint() const  = 0;

    // Defining the ratio DefaultTensionTangency/RealTensionTangency 
    // 1.0 is default ; 
    virtual void SetTangencyRatio(const double iTensionRatio)= 0;
    virtual double GetTangencyRatio() const=0;

    // 0 : Matching creates only a local deformation.
    // 1 : Deformation will be equally diffused along the STBM.
    virtual void SetPropagation(const CATLONG32 ipropagation) = 0;
    virtual CATLONG32 GetPropagation() const = 0;

   
    // If iOrient=1 then the side of the reference curve used for the C1 match 
    // is in the same direction as the parametrization of the curve;
    // If iOrient=-1 then the side is in the opposite direction.
    virtual void SetTangentOrientation(CATLONG32 iOrient) = 0;
    virtual CATLONG32 GetTangentOrientation() const = 0;
  
};
#endif





