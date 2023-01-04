#ifndef CATPGMFrFUtiBipar_h_
#define CATPGMFrFUtiBipar_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"

class CATCrvLimits;
class CATCurve;
class CATFrFCombMF;
class CATFrFCompositeCurve;
class CATFrFNurbsBipar;
class CATFrFNurbsMultiForm;
class CATGeoFactory;
class CATKnotVector;
class CATMathNurbsBipar;
class CATMathNurbsMultiForm;
class CATMathPolynomX;
class CATMathVector;
class CATNurbsSurface;
class CATPCurve;
class CATPLine;
class CATSoftwareConfiguration;


ExportedByCATGMOperatorsInterfaces CATFrFNurbsBipar *CATPGMMakeNurbsSurfaceClamped(
        CATGeoFactory            * iFactory            ,
        CATSoftwareConfiguration * iConfig             ,
  const CATLONG32                  iOrderU             ,
  const CATLONG32                  iKnotSizeU          ,
        double                   * iExtendedKnotVectorU,
  const CATLONG32                  iOrderV             ,
  const CATLONG32                  iKnotSizeV          ,
        double                   * iExtendedKnotVectorV,
  const CATLONG32                  iIsRational         ,
  const CATLONG32                  iIsPeriodic         ,
        CATLONG32                  iNumberOfPoleU      ,
        CATLONG32                  iNumberOfPoleV      ,
        double                   * iPole               ,
        double                   * iWeight             ,
  const double                     iTolEqualKnots      );


// DEPRECATED, not XScale compliant, will soon disappear, use API with factory and software configuration, above
ExportedByCATGMOperatorsInterfaces CATFrFNurbsBipar *CATPGMMakeNurbsSurfaceClamped(
  const CATLONG32                  iOrderU             ,
  const CATLONG32                  iKnotSizeU          ,
        double                   * iExtendedKnotVectorU,
  const CATLONG32                  iOrderV             ,
  const CATLONG32                  iKnotSizeV          ,
        double                   * iExtendedKnotVectorV,
  const CATLONG32                  iIsRational         ,
  const CATLONG32                  iIsPeriodic         ,
        CATLONG32                  iNumberOfPoleU      ,
        CATLONG32                  iNumberOfPoleV      ,
        double                   * iPole               ,
        double                   * iWeight             ,
  const double                     iTolEqualKnots      );

#endif /* CATPGMFrFUtiBipar_h_ */
