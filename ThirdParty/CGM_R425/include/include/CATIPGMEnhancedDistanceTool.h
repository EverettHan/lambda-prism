#ifndef CATIPGMEnhancedDistanceTool_h_
#define CATIPGMEnhancedDistanceTool_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMDistanceTool.h"
#include "CATDataType.h"

class CATCompositeLaw;
class CATCrvParam;
class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATPCurve;
class CATSoftwareConfiguration;
class CATSurParam;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMEnhancedDistanceTool;

class ExportedByCATGMModelInterfaces CATIPGMEnhancedDistanceTool: public CATIPGMDistanceTool
{
public:
  /**
   * Constructor
   */
  CATIPGMEnhancedDistanceTool();

  //
  // ValidateInitSide
  //   Return values :  -1 - Unimplemented (or bad CGMLevel)
  //                     0 - Wrong side
  //                     1 - Right side
  // The right side is given by taking into account :
  //  - GetSide() * CATSign(iRadiusValue), which gives the side of the parallel curve
  //  - N ^ V where N = normal at iSurParam and V = tangent at iCrvParam, 
  //    which gives the positive side.
  // In degenerated cases (null radius for example), iTangent3D must also be considered.
  // It is tangent to the expected result.
  //
  virtual CATLONG32 ValidateInitSide(
    CATCurve *iCurve,
    CATCrvParam &iCrvParam,
    CATSurface *iSurface,
    CATSurParam &iSurParam,
    double iRadiusValue,
    double *iTangent3D,
    double *oProduct = NULL) = 0;

  //
  // ProjectOnOriginal Surface
  // iCurve et iParam courbe initiale et parametre initiale
  // oOriginialSurface  surface sur laquelle on est pose
  // oOriginalPCurve pcurve originale correspondat au param et a la courbe orginale
  // oParam CrvParam de la PCurve equivalent au iParam initial
  // oCorrespondingParam surParam equivalent au iParam initial
  virtual CATLONG32 ProjectOnOriginalSurface(
    CATCurve *iCurve,
    CATCrvParam &iParam,
    CATSurface *&oOriginalSurface,
    CATPCurve *&oOriginalPCurve,
    CATCrvParam &oParam,
    CATSurParam &oCorrespondingParam) = 0;

  //
  // GetMaps2DCurve: permet de retrouver la correspondante 2D d'une courbe 3D
  //suite au clean input 3D du parallele
  virtual CATEdgeCurve *GetMaps2DCurve(CATCurve *iCurve, CATCrvParam &iCrvParam) = 0;

  //
  // GetType
  //   Return values : 5 - Euclidean Parallel type
  //                   6 - Geodesic Parallel type
  //
  //virtual CATLONG32 GetType () = 0;
  // To retrieve smoothing option (internal use only)
  virtual void GetNewSmoothing(CATLONG32 &oSmooth) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMEnhancedDistanceTool(); // -> delete can't be called
};

#endif /* CATIPGMEnhancedDistanceTool_h_ */
