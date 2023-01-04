#ifndef CATSGMC1GeoUtilities_h_
#define CATSGMC1GeoUtilities_h_

// COPYRIGHT DASSAULT SYSTEMES 2008

#include "CATSGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATParameterizationOption.h"

class CATGeoFactory;
class CATKnotVector;
class CATMathGridOfPoints;
class CATMathSetOfPoints;
class CATNurbsCurve;
class CATNurbsSurface;

class ExportedByCATSGMOperatorsInterfaces CATSGMC1GeoUtilities
{
public:
  /**
   * Constructor
   */
  CATSGMC1GeoUtilities();

  /**
   * Destructor
   */
  virtual ~CATSGMC1GeoUtilities();

  // method to create a C1 Factory (Factory that will support C1 geometries)
  static CATGeoFactory *CATCreateC1CGMContainer();

  // method to create a NurbsCurve at least C1 
  static CATNurbsCurve *CATCreateC1NurbsCurve(
    CATGeoFactory *iFactory,
    const CATKnotVector &iKnotVector,
    const CATLONG32 &iIsRational,
    const CATMathSetOfPoints &iVertices,
    const double *iWeights,
    const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization);

  // method to create a NurbsSurface at least C1 
  static CATNurbsSurface *CATCreateC1NurbsSurface(
    CATGeoFactory *iFactory,
    const CATKnotVector &iKnotVectorU,
    const CATKnotVector &iKnotVectorV,
    const CATLONG32 &iIsRational,
    const CATMathGridOfPoints &iVertices,
    const double *iWeights,
    const CATParameterizationOption iParameterizationOption = CatAutomaticParameterization);

};

#endif /* CATSGMC1GeoUtilities_h_ */
