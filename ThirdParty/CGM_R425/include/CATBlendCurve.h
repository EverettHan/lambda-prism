// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATBlendCurve:
// Interface class of the Blend Curve Operator.
//
//==========================================================================
//
// Usage notes:
// This class can be used as is for simple Blend or derived
// in order to implement specific algorithm or capabilities.
//
//========================================================================== 
// 09/97     Creation                       Tuan Phung (tpg)
// 07/03     Ajout SetSlideDirection
//========================================================================== 

#ifndef CATBlendCurve_H
#define CATBlendCurve_H

#include "CATGMOperatorsInterfaces.h"

#include "CATMathDef.h"
#include "CATCrvParam.h"
#include "CATCGMVirtual.h"
#include "CATMathDirection.h"
#include "CATPGMCreateBlendCurve.h"

class CATCurve;
class CATSoftwareConfiguration;
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATBlendCurve : public CATCGMVirtual
  {
  public :
    
    virtual ~CATBlendCurve();

    virtual void SetSoftwareConfiguration(CATSoftwareConfiguration* iConfig) = 0;

    //
    //  Setting the blend limit curves 
    //
    virtual void SetCurve(const CATLONG32 iSide, const CATCurve *iCurve)=0;

    virtual void SetCurveParam(const CATLONG32 iSide, const CATCrvParam &iCrvParam)=0;
    
    //
    //  Setting the blend configuration 
    //
    //this method has to be called before Run. It is in fact a Get and a Set method.
    //iMode=0 is the standard mode as specified by topological operator.
    //iMode=1 is the mode in which we try to minimize the length of the solution.
    virtual void SetDefaultConfiguration(CATLONG32 &oTransitionOrientationSide1,
                                         CATLONG32 &oTransitionOrientationSide2,
                                         CATLONG32 iMode=0)=0;

    virtual void SetTransitionContinuity(const CATLONG32 iSide,
                                         const CATLONG32 iTransitionContinuity)=0;

    virtual void SetTransitionOrientation(const CATLONG32 iSide,
                                          const CATLONG32 iTransitionOrientation)=0;
    //
    //  Setting the blend parameters 
    //
    virtual void SetTangencyParameter(const CATLONG32 iSide,
                                      const double TangencyParameter)=0;

    virtual void SetCurvatureParameter(const CATLONG32 iSide,
                                       const double CurvatureParameter)=0;
    
    virtual void SetBeforeCXR6()=0;
    //
    //  Setting the Support Trimming Mode 
    //
    //  iMode = 0 : Off 
    //  iMode = 1 : On
    //  
    virtual void SetSupportTrimmingMode(const CATLONG32 iMode)=0;
    //
    // iActivate = 0: Off
    // iActivate = 1: On ; Direction are used
    virtual void SetSlideDirection(CATLONG32 iActivate, CATMathDirection SlideDir[2]) =0;
    //
    //
    // Unify Sur/Crv soft by defaut ( used by freestyle without topology )
    // False vhen used by CATTopologicalBlendCurve
    virtual void SetUseSurfacicBehaviour(CATBoolean SurfacicBehaviour=TRUE)=0;

    //
    virtual void Run()=0;
   
    //
    //  Getting the blend result 
    // 
    virtual CATLONG32 GetNumberOfBlends() const=0;
    virtual void BeginningBlend()=0;
    virtual CATBoolean NextBlend()=0;
    virtual CATCurve *GetCurve() const=0;
    //
    virtual CATCurve *GetFirstTrimmedCurve() const=0;
    virtual CATCurve *GetSecondTrimmedCurve() const=0;
    
  };

#endif
