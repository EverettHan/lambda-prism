// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATFillSurface:
// Interface class of the Fill Surface Operator.
//
//==========================================================================
//
// Usage notes:
// This class can be used as is for simple Fill or derived
// in order to implement specific algorithm or capabilities.
//
//========================================================================== 
// July 97     Creation                       Tuan Phung
//========================================================================== 

#ifndef CATFillSurface_H
#define CATFillSurface_H

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
#include "CATCGMVirtual.h"

#include "CATPGMCreateFillSurface.h"

class CATNurbsSurface;
class CATCurve;
class CATCrvLimits;
class CATMathPlane;
class CATMathPoint;
class CATFrFNurbsBipar;
class CATSoftwareConfiguration;
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATFillSurface : public CATCGMVirtual
{
  public :

    virtual ~CATFillSurface();
    virtual void Run()=0;
//
//  Setting tolerance
//
//  iContinuity = 0 : G0 tolerance (model unit)
//  iContinuity = 1 : G1 tolerance (degree)
    virtual void SetTolerance(CATLONG32 iContinuity,double iTolerance)=0;
//
//  Getting tolerance
//
    virtual void GetTolerance(CATLONG32 iContinuity,double &oTolerance)=0;
//
//  Setting the Fill configuration 
//
    virtual void SetTransitionContinuity(const CATLONG32 iside, 
                                         const CATLONG32 itransitioncontinuity)=0;
//
//  Setting the Fill parameters 
//
    virtual void SetTangencyParameter(const CATLONG32 iside,
				      const double tangencyparameter)=0;
// 
//  Triangular patch creation
//
//  iMode = 1: Yes
//  iMode = 0: No (default option)
    virtual void SetTriangularPatchCreation(const CATLONG32 iMode=1)=0;
//
//  Getting the Fill result 
// 
    virtual CATLONG32 GetNumberOfFills() const=0;
    virtual void BeginningFill()=0;
    virtual CATBoolean NextFill()=0;
    virtual CATNurbsSurface **GetSubSurfaces() const=0;
    virtual CATLONG32 GetNumberOfSubSurfaces() const=0;
    virtual CATLONG32 GetAdjacentSide(CATNurbsSurface * iSubSurface,
				 CATLONG32 iBorderOfSubSurface)=0;
//
//  Center point management
//  useless when filling a four side hole
//
    virtual void GetCenterPoint(CATMathPoint *&oCenterPoint)=0;
    virtual void SetCenterPoint(CATMathPoint * iCenterPoint)=0;  
    virtual void ResetCenterPoint()=0; 
//
// Get the Affine Space (plane)
// returns 0 if failure 
    virtual int GetAffinePlane(double iMaxDistance,
				      CATMathPlane *&oMathPlane,
				      CATFrFNurbsBipar *&oNurbsBipar)=0;

//
// To avoid optimization on combs,
// for example if they are already done.
  virtual void SetNoOptimization()=0;

//
// To specify current version.
  virtual void SetSoftwareConfiguration(CATSoftwareConfiguration* iConfig)=0;

//
// param  iDegreeU 
// the required degree in  U of the result surface 
// param iDegreeV
// the required degree in  V of the result surface 
// param  iNumberUOfPatch
// the required maximum number of patches in  U of the result surface 
// param  iNumberVOfPatch
// the required maximum number of patches in  V of the result surface 
// Only available in G1S4 type (4-sided loop).
  virtual void SetSurfaceParameters ( int iDegreeU, int iDegreeV, int iNumberUOfPatch, int iNumberVOfPatch)=0;

};

#endif
