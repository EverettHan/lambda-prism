#ifndef CATISGMGeometricObjItfBldr_h
#define CATISGMGeometricObjItfBldr_h

#include "ExportedByCATGMGeometricInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATParameterizationOption.h"
#include "CATDataType.h"

class CATGeoFactory;
class CATNurbsCurve;
class CATKnotVector;
class CATMathSetOfPoints;
class CATNurbsSurface;
class CATMathGridOfPoints;

extern ExportedByCATGMGeometricInterfaces IID IID_CATISGMGeometricObjItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework TopologicalOperatorsLight.
 */
class ExportedByCATGMGeometricInterfaces CATISGMGeometricObjItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATGeoFactory *CATC1GeoUtilities_CATPGMCreateC1CGMContainer() = 0;

  virtual CATNurbsCurve *CATC1GeoUtilities_CATPGMCreateC1NurbsCurve(
    CATGeoFactory *iFactory,
    const CATKnotVector &iKnotVector,
    const CATLONG32 &iIsRational,
    const CATMathSetOfPoints &iVertices,
    const double *iWeights,
    const CATParameterizationOption iParameterizationOption) = 0;

  virtual CATNurbsSurface *CATC1GeoUtilities_CATPGMCreateC1NurbsSurface(
    CATGeoFactory *iFactory,
    const CATKnotVector &iKnotVectorU,
    const CATKnotVector &iKnotVectorV,
    const CATLONG32 &iIsRational,
    const CATMathGridOfPoints &iVertices,
    const double *iWeights,
    const CATParameterizationOption iParameterizationOption) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework TopologicalOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMGeometricInterfaces CATISGMGeometricObjItfBldr *CATSGMGetGeometricObjItfBldr();

#endif /* CATISGMGeometricObjItfBldr_h */
