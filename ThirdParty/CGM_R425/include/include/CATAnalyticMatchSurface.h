// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATAnalyticMatchSurface:
// Interface class of the Analytic Match Surface Operator.
//
//=============================================================================
//
// Usage notes:
// This class can be used as is for simple Match or derived
// in order to implement specific algorithm or capabilities.
//
//=============================================================================
// August   97     Creation                       C.  Vergez-Samblancat
// Novembre 97     Modification                   J.  Bouix
// January  99     Modification                   P-A Lourme
//=============================================================================

#ifndef CATAnalyticMatchSurface_H
#define CATAnalyticMatchSurface_H

#include "CATMatchSurface.h"
#include "CATGMOperatorsInterfaces.h"

//-----------------------------------------------------------------------------
class  ExportedByCATGMOperatorsInterfaces CATAnalyticMatchSurface : public CATMatchSurface
{
  public :
    
    virtual  ~CATAnalyticMatchSurface();

    //=========================
    //  N E W   M E T H O D S 
    //=========================
    // Setting the Reference curve on which the STBM has to be matched.
    virtual void SetCurveReference(const CATCurve *iCurveRef ) = 0; 
    virtual void SetCurveLimits(const CATCrvLimits &iCrvLimits) = 0; 
    // Tangent Continuity Mode (with a connection continuity = 1)
    // The default value is iTgtCont = CATFrFCrossTgtCont
    virtual void SetTangentContinuity(const CATFrFTangentContinuity iTgtCont) = 0;
    virtual CATFrFTangentContinuity GetTangentContinuity() const = 0;
    // Cross Tangent Ratio Mode (with connection continuity >= 1 
    //			         and  tangent continuity == CATFrFCrossTgtCont)
    // The operator applies a ratio (between the reference and the STBM) on the 
    // reference tangent norm. There are four possible ratio values 
    // iMode = 0 : The ratio of the cross tangents' mean value is adopted.
    // iMode = 1 : The ratio of the initial cross tangents is adopted.
    // iMode = 2 : The ratio of the final cross tangents is adopted.
    // iMode = 3 : The ratios at the initial and final cross tangents are maintained,
    //             (a linear law is adopted)
    // The default values is iMode = 0.
    virtual void SetCrossTangentRatio(const CATLONG32 iRatio) = 0;
    virtual CATLONG32 GetCrossTangentRatio() const = 0;

  
    //=========================
    //  O L D   M E T H O D S 
    //=========================
    //  Type of transition continuity
    // 1  : C0 (Default)
    // 2  : Colinear normals (G1)       
    // 21 : Colinear tangents (between STBM and Reference) at the end
    // 22 : Colinear tangents at the beginning
    // 3  : Colinear tangents (C1)
    // 4  : Curvature continuity (C2)
    // 5  : Variable angle between normals and variable tension of tangencies
    virtual void SetTransitionContinuity(const CATLONG32 Continuity) = 0;
    virtual CATLONG32 GetTransitionContinuity() const = 0; 
    // Angle between normals to surfaces at the begin and at the end of 
    // the boundary, (0.0,0.0) is the default ;
    // if angles are not same, a linear law is applied. 
    // Must be used with ContinuityMode = 5 
    virtual void SetBeginNormalAngle(const double iBeginAngle) = 0;
    virtual void SetEndNormalAngle(const double iEndAngle) = 0;
    virtual void GetNormalAngle(double &oBeginA, double &oEndA )const=0;
    // Defining the ratio DefaultTensionTangency/RealTensionTangency 
    // on the boundary, 1.0 is default ;
// LGNLGN1Deb
    virtual void SetTangencyRatio(double iTensionRatio) = 0;
    virtual double GetTangencyRatio() const = 0;
// LGNLGN1Fin
    // Defining the ratio DefaultTensionTangency/RealTensionTangency at 
    // the begin and at the end of the boundary, (1.0,1.0) is the default ; 
    // if ratios are not same, a linear law is applied. 
    // Must be used with ContinuityMode = 5 
    virtual void SetBeginTangencyRatio(const double iBeginTensionRatio)= 0;
    virtual void SetEndTangencyRatio(const double iEndTensionRatio)= 0;
    virtual void GetTangencyRatio(double &oBeginTR, double &oEndTR )const=0;
    // 0 : Matching creates only a local deformation.
    // 1 : Deformation will be equally diffused along the STBM.
    virtual void SetPropagation(const CATLONG32 ipropagation) = 0;
    virtual CATLONG32 GetPropagation() const = 0;
    // For ExactMatching == 1, the matching is analytic and exact, i.e.
    // it could change the longitudinal degree of the surface to be match.
    // For ExactMatching == 0, the matching is at best without changing the 
    // longi. degree of the surface to be match or with specified degrees 
    // (see below).
    virtual void SetHomogeneization(const CATLONG32 ExactMatching) = 0;
    virtual CATLONG32 GetHomogeneization() const = 0;
    // Longitudinal and transversal degrees constraint,
    // these methods should be call with ExactMatching == 0.
    // Default Values are original degrees of the STBM. 
    virtual void GetDegree(CATLONG32 &NLongi , CATLONG32 &NTrans) const = 0;
    virtual void SetDegreeLongi(CATLONG32 NLongi) = 0; 
    virtual void SetDegreeTrans(CATLONG32 NTrans) = 0;

};
#endif





