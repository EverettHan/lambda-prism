#ifndef CATValidOffset_H
#define CATValidOffset_H

// COPYRIGHT DASSAULT SYSTEMES 1999

// class for determining areas where  an offset of a surface 
// can be defined.
//
// This operator only treats the following case : variable fillet surface
// and cone 

#include "Y30C3XGG.h"

#include "CATSurLimits.h"
#include "CATSkillValue.h"
#include "CATIsoParameter.h"
#include "CATHomotopyDef.h"
#include "CATCGMVirtual.h"

class CATGeoFactory;
class CATSurface;
class CATPCurve;
class CATSoftwareConfiguration;

class ExportedByY30C3XGG CATValidOffset  : public CATCGMVirtual
{
public:
  
  // Constructor
     
  CATValidOffset(CATGeoFactory *iFactory,
	  CATSoftwareConfiguration  * pConfig,
    CATSurface *iSurface,
    double ROffset,
    CATSkillValue iMode=BASIC);
  
  ~CATValidOffset();

  void Run();
  
  // Initializes the iterator for the resulting curves
  
  void BeginningCurve();
  
  // skips to the next curve
  
  CATBoolean NextCurve();
  
  // Returns the number of curves
  
  CATLONG32 GetNumberOfCurves();
  
  // Is an isopar
  
  CATIsoParameter IsAnIsopar();
  
  // IsA3DPoint : returns 1 if the curve is a 3D point
  
  CATLONG32 IsA3DPoint();
  
  // Returns the value of u or v for an isopar
  
  void GetIsopar(double &oUV);
  
  // Creates the current curve in a more general case
  //
  // CATSideToOffset = {CATSideLeftToOffset, CATSideRightToOffset}
  // indicates where the surface is offsetable : at the left,
  // the right or both sides of the PCurve
  
  CATPCurve * GetCurve(CATSideToOffset & oSide);
 
private:
  
  // private methods 
  void FilletVarCalc();
  void ConeCalc();
  void StoreIsoparamSolution(double iUV, CATIsoParameter iIsoPar);
  
  // private variables
  CATGeoFactory * _Factory;
  CATSurface * _Surface;
  const CATSurface * _GeometricRep;
  CATSurLimits _MaxLimits;
  double _R;
  CATLONG32 _NumberOfCurves;
  CATLONG32 _NumberOfCurvesAlloc;
  CATLONG32 _CurrentCurve;
  CATIsoParameter * _IsAnIsopar;
  double *_uv;
  CATSideToOffset * _DiagSide;
  // Config
  CATSoftwareConfiguration * _SoftwareConfiguration;

};

#endif
